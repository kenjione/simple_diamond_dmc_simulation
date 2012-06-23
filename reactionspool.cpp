#include "reactionspool.h"

#include <iostream>
#include <cmath>

ReactionsPool::ReactionsPool(Surface *surface, Crystal *crystal) :
    _absH(surface), _addH(surface),
    _formDimer(surface, crystal), _dropDimer(surface),
    _addCH2(surface, crystal), _etching(surface, crystal),
    _migrationH(surface), _migrationBridge(surface, crystal), _migrationFrontDown(surface, crystal)
{
    _reactions.push_back(&_absH);
    _reactions.push_back(&_addH);
    _reactions.push_back(&_etching);
    _reactions.push_back(&_migrationBridge);
    _reactions.push_back(&_addCH2);
    _reactions.push_back(&_formDimer);
    _reactions.push_back(&_dropDimer);
    _reactions.push_back(&_migrationH);
    _reactions.push_back(&_migrationFrontDown);
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
    names.push_back("migration front down");
    return names;
}

std::deque<int> ReactionsPool::reactionsTimes() const {
    std::deque<int> times;
    for (Reaction *reaction : _reactions) {
        times.push_back(reaction->times());
    }

    return times;
}

void ReactionsPool::seeAtActives(const std::set<Carbon *> &activeCarbons) {
    for (Carbon *carbon : activeCarbons) {
        _addH.seeAt(carbon);
        _formDimer.seeAt(carbon, 0);
        _migrationFrontDown.seeAt(carbon);
    }
}

void ReactionsPool::seeAtHydrogens(const std::set<Carbon *> &hydroCarbons) {
    for (Carbon *carbon : hydroCarbons) {
        _absH.seeAt(carbon);
        _migrationBridge.seeAt(carbon);
        _etching.seeAt(carbon);
    }
}
void ReactionsPool::seeAtDimer(const std::map<Carbon *, Carbon *> &dimers) {
    for (auto &carbonsPair : dimers) {
        // TODO: стоит пересмотреть метод SeeAt для DualReaction, в плане аргументов (чтобы принмало &pair вместо двух Carbon *)
        _addCH2.seeAt(carbonsPair.first, carbonsPair.second);
        _dropDimer.seeAt(carbonsPair.first, carbonsPair.second);
        _migrationH.seeAt(carbonsPair.first, carbonsPair.second);
    }
}

double ReactionsPool::doReaction() {
    double *commonRates = new double[_reactions.size()];
    for (unsigned int i = 0; i < _reactions.size(); ++i) {
        commonRates[i] = _reactions[i]->commonRate();
    }

    // нормируем реакции.
    double tr = totalRate();
    double *valuetedRates = new double[_reactions.size()];
    for (unsigned int i = 0; i < _reactions.size(); ++i) {
        valuetedRates[i] = commonRates[i] / tr;
//        std::cout << valuetedRates[i] << std::endl;
    }

    // строим линию
    for (unsigned int i = 1; i < _reactions.size(); ++i) {
        valuetedRates[i] += valuetedRates[i-1];
    }

    auto random01 = []() { return rand() / double(RAND_MAX); };
    // кидаем случайное число, выбираем реакцию и проводим ее.
    double reactionIndex = random01();
    double dt = 0;

    for (unsigned int i = 0; i < _reactions.size(); ++i) {
        if (reactionIndex < valuetedRates[i]) {
            _reactions[i]->doIt();
            _reactions[i]->incTimes();

            double random = 0.0;
            while (random == 0.0) random = random01();
            dt = -log(random) / commonRates[i];
            break;
        }
    }

    delete [] valuetedRates;
    delete [] commonRates;

//    std::cout << "\ndt = " << dt << std::endl;
    return dt;
}

void ReactionsPool::reset() {
    for (Reaction *reaction : _reactions) reaction->reset();
}

FormDimerReaction &ReactionsPool::formDimerReaction() {
    return _formDimer;
}

// считаем сумму скоростей во всем реакциям.
double ReactionsPool::totalRate() {
    double sum = 0.0;
    for (Reaction *reaction : _reactions) sum += reaction->commonRate();
    //std::cout << "\n    ...sumRate: " << sum << std::endl;
    return sum;
}
