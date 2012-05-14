#include <iostream>
#include "surface.h"

#include "abshreaction.h"
#include "addhreaction.h"
#include "etchingreaction.h"
#include "migrationbridgereaction.h"
#include "addch2reaction.h"
#include "formdimerreaction.h"
#include "dropdimerreaction.h"
#include "migrationhreaction.h"
#include "reactor.h"


#include <iostream>

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    std::cout << "call Surface::Surface()\n";
    init();
}

Surface::~Surface() {
// TODO Увверен, что это нужно?
//    for (int i = 0; i < 8; i++) delete _reactions[i];
//    delete _reactions;
}

void Surface::init() {

    std::cout << "call Surface::init()\n";

    _crystal->init();
    _crystal->throughAllCarbonsIter(std::ref(*this));

    std::cout << "hydrocarbons: " << this->_hydroCarbons.size() << std::endl;
    std::cout << "active carbons: " << this->_activeCarbons.size() << std::endl;
}

float Surface::doReaction() {
    std::cout << "call Surface::doReaction()\n";

    // жёстко, но действенно.

    AbsHReaction *abshreaction = new AbsHReaction(this);
    AddHReaction *addhreaction= new AddHReaction(this);
    EtchingReaction *etchingreaction= new EtchingReaction(this, _crystal);
    MigrationHReaction *migrationhreaction = new MigrationHReaction(this);
    AddCH2Reaction *addch2reaction = new AddCH2Reaction(this, _crystal);
    FormDimerReaction *formdimerreaction = new FormDimerReaction(this, _crystal);
    DropDimerReaction *dropdimerreaction= new DropDimerReaction(this);
    MigrationBridgeReaction *migrationbridgereaction= new MigrationBridgeReaction(this, _crystal);


    // проверка на работоспособность каждой реакции.

    for (Carbon *carbon : _activeCarbons) {
        // 1) осаждение водорода
        addhreaction->seeAt(carbon);
        // 3) формирование димера
        formdimerreaction->seeAt(carbon, 0);
    }

    for (Carbon *carbon : _hydroCarbons) {
        // 2) удаление водорода
        abshreaction->seeAt(carbon);
    }

    for (auto &carbons_pair : _dimerBonds) {
        // 4) осаждение СН3
        // TODO: стоит пересмотреть метод SeeAt для DualReaction, в плане аргументов (чтобы принмало &pair вместо двух Carbon *)
        addch2reaction->seeAt(carbons_pair.first, carbons_pair.second);
    }

    // TODO: мы сначала смотрим всеми реакциями, затем нормируем по commonRate, а уже затем выполняем случайную реакцию через doIt

//    for (std::set<Carbon*>::const_iterator i = _activeCarbons.begin(); i != _activeCarbons.end(); i++) addhreaction->seeAt(*i);
//        addhreaction->doIt();

//    // 2) удаление водорода
//  //  for (std::set<Carbon*>::const_iterator i = _hydroCarbons.begin(); i != _hydroCarbons.end(); i++) abshreaction->seeAt(*i);
//  //      abshreaction->doIt();

//    // 3) формирование димера
//    for (std::set<Carbon*>::const_iterator i = _activeCarbons.begin(); i != _activeCarbons.end(); i++) formdimerreaction->seeAt(*i,0);
//        formdimerreaction->doIt();

//    std::map<Carbon*, Carbon*>::iterator i = _dimerBonds.begin();

//    //std::cout << (*i).first << std::endl;
//    //std::cout << (*i).second << std::endl;
//    // 4) осаждение СН3

//    for (std::map<Carbon*, Carbon*>::iterator i = _dimerBonds.begin(); i != _dimerBonds.end(); i++)
//    {
//        //std::cout << (*i).first << std::endl;
//        addch2reaction->seeAt((*i).first, (*i).second);
//    }
//    addch2reaction->doIt();

    /*


      // TODO

    // 4) разрыв димера


    // 5)


    // 6) миграция СН2
    // 7) травление
    // 8) Миграция водорода.


    */


    // считать коммон рейт по всем скоростям.
    // нормировать.
    // кинуть и выбрать реакцию.
    // провести ее.
    // зачекать изменения.
    // сохранить.
    // repeat.

    delete abshreaction;
    delete addhreaction;
    delete etchingreaction;
    delete migrationhreaction;
    delete addch2reaction;
    delete formdimerreaction;
    delete dropdimerreaction;
    delete migrationbridgereaction;

    // TODO должно возращать dt реакции
//    return dt;
}

void Surface::operator() (Carbon *carbon) {

    //std::cout << "call Surface::operator()\n";
    //std::cout << "this carbon properties: \n  actives: " << carbon->actives() << "\n  hydro: " << carbon->hydrogens() << "\n\n";
    if (carbon->actives() > 0) _activeCarbons.insert(carbon);
    if (carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
}

void Surface::addHydrogen(Carbon *carbon) {
    carbon->addHydrogen();
    _hydroCarbons.insert(carbon);
    if (carbon->actives() == 0) _activeCarbons.erase(carbon);
}

void Surface::removeHydrogen(Carbon *carbon) {
    carbon->absHydrogen();
    _activeCarbons.insert(carbon);
    if (carbon->hydrogens() == 0) _hydroCarbons.erase(carbon);
}

void Surface::addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->addCarbon(carbon);

    bottomFirst->formBond();
    bottomSecond->formBond();

    _hydroCarbons.insert(carbon);
    if (bottomFirst->actives() == 0) _activeCarbons.erase(bottomFirst);
    if (bottomSecond->actives() == 0) _activeCarbons.erase(bottomSecond);
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->removeCarbon(carbon);

    bottomFirst->dropBond();
    bottomSecond->dropBond();

    _hydroCarbons.erase(carbon); // т.к. только те, что с водородами могут отлетать (проверка внутри реакции)
    _activeCarbons.insert(bottomFirst);
    _activeCarbons.insert(bottomSecond);
}

void Surface::moveCarbon(Carbon *carbon, const int3 &to,
                         const std::pair<Carbon *, Carbon *> &fromBasis,
                         const std::pair<Carbon *, Carbon *> &toBasis)
{
    _crystal->move(carbon, to);

    /*
        надо разорвать димер так чтобы у него не было активных связей,
        т.к димерная связь идет на мостовую группу. Аналогичная ситуация
        и с образованием димера после перемещения мостовой группы.
    */

    // добавление к димерам
    // TODO: димер не образуется автоматически, при миграции мостовой группы, образуются просто активные связи
    Carbon *first = fromBasis.first;
    first->dropBond();
    _activeCarbons.insert(first);
    Carbon *second = fromBasis.second;
    fromBasis.second->dropBond();
    _activeCarbons.insert(second);
//    _dimerBonds[first] = second;



    // удаление из димеров
    first = toBasis.first;
    second = toBasis.second;
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        it = _dimerBonds.find(second);
    }

    if (it != _dimerBonds.end()) {
        _dimerBonds.erase(it);
        first->setAsNotDimer();
        second->setAsNotDimer();
    } else {
        // может мигрировать не только на димеры, но и на активные атомы
        first->formBond();
        second->formBond();
    }
}


void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
//    _dimerBonds[second] = first;

    first->formBond();
    second->formBond();

    first->setAsDimer();
    second->setAsDimer();

    if (first->actives() == 0) _activeCarbons.erase(first);
    if (second->actives() == 0) _activeCarbons.erase(second);
}

void Surface::dropDimer(Carbon *first, Carbon *second) {
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(second);
    }

    _dimerBonds.erase(it); // удаляем димер из хеша

    second->dropBond();
    first->dropBond();

    first->setAsNotDimer();
    second->setAsNotDimer();

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());

    return allSites.size();
}
