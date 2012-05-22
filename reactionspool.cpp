#include "reactionspool.h"

#include <iostream>
#include <cmath>

ReactionsPool::ReactionsPool(Surface *surface, Crystal *crystal) :
    _absH(surface), _addH(surface), _formDimer(surface, crystal), _dropDimer(surface),
    _addCH2(surface, crystal), _etching(surface, crystal), _migrationBridge(surface, crystal), _migrationH(surface)
{
    _reactions[0] = &_absH;
    _reactions[1] = &_addH;
    _reactions[2] = &_etching;
    _reactions[3] = &_migrationBridge;
    _reactions[4] = &_addCH2;
    _reactions[5] = &_formDimer;
    _reactions[6] = &_dropDimer;
    _reactions[7] = &_migrationH;
}

std::deque<std::string> ReactionsPool::reactionsNames() const {
    std::deque<std::string> names;
    names.push_back("abstraction H");
    names.push_back("addition H");
    names.push_back("etching bridge");
    names.push_back("migration bridge");
    names.push_back("addition bridge");
    names.push_back("form dimer");
    names.push_back("drop dimer");
    names.push_back("migration H");
    return names;
}

std::deque<int> ReactionsPool::reactionsTimes() const {
    std::deque<int> times;
    for (int i = 0; i < REACTIONS_NUM; i++) {
        times.push_back(_reactions[i]->times());
    }

    return times;
}

void ReactionsPool::seeAtActives(std::set<Carbon *> activeCarbons) {

//    std::cout << "\n (param) Active: " << activeCarbons.size();

    for (Carbon *carbon : activeCarbons) {
        _addH.seeAt(carbon);
        _formDimer.seeAt(carbon, 0);
    }
}

void ReactionsPool::seeAtHydrogens(std::set<Carbon *> hydroCarbons) {

//    std::cout << "\n (param) Hydro: " << hydroCarbons.size();

    for (Carbon *carbon : hydroCarbons) {
        _absH.seeAt(carbon);
        _migrationBridge.seeAt(carbon);
        _etching.seeAt(carbon);
    }
}
void ReactionsPool::seeAtDimer(std::map<Carbon *, Carbon *> dimers) {

//    std::cout << "\n (param) Dimers: " << dimers.size();

    for (auto &carbons_pair : dimers) {
        // TODO: стоит пересмотреть метод SeeAt для DualReaction, в плане аргументов (чтобы принмало &pair вместо двух Carbon *)
        _addCH2.seeAt(carbons_pair.first, carbons_pair.second);
        _dropDimer.seeAt(carbons_pair.first, carbons_pair.second);
//        _migrationH.seeAt(carbons_pair.first, carbons_pair.second);
    }
}

double ReactionsPool::doReaction() {

    double commonRates[8];
    for (int i = 0; i < REACTIONS_NUM; i++) commonRates[i] = _reactions[i]->commonRate();

    // нормируем реакции.
    double valuetedRates[8];
    double tr = totalRate();
    for (int i = 0; i < 8; i++) {
        valuetedRates[i] = commonRates[i] / tr;
//        std::cout << valuetedRates[i] << std::endl;
    }

    // строим линию
    for (int i = 1; i < 8; i++) valuetedRates[i] += valuetedRates[i-1];

    auto random01 = []() { return rand() / double(RAND_MAX); };
    // кидаем случайное число, выбираем реакцию и проводим ее.
    double reactionIndex = random01();
    double dt = 0; 

    for (int i = 0; i < REACTIONS_NUM; i++) {
        if (reactionIndex < valuetedRates[i]) {
            _reactions[i]->doIt();
            _reactions[i]->incTimes();

            double random = 0.0;
            while (random == 0.0) random = random01();
            dt = -log(random) / commonRates[i];
            break;
        }
    }

//    std::cout << "\ndt = " << dt << std::endl;
    return dt;
}

void ReactionsPool::reset() {
    for (int i = 0; i < REACTIONS_NUM; i++) _reactions[i]->reset();
}

// считаем сумму скоростей во всем реакциям.
double ReactionsPool::totalRate() {
    double sum = 0.0;
    for (int i = 0; i < REACTIONS_NUM; i++) sum += _reactions[i]->commonRate();
    //std::cout << "\n    ...sumRate: " << sum << std::endl;
    return sum;
}
