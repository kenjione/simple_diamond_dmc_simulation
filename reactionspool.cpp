#include "reactionspool.h"


#include <iostream>
#include <cmath>

ReactionsPool::ReactionsPool(Surface *surface, Crystal *crystal) :
    _absH(surface), _addH(surface), _formDimer(surface, crystal), _dropDimer(surface),
    _addCH2(surface, crystal), _etching(surface, crystal), _migrationBridge(surface, crystal), _migrationH(surface)
{

    _reactions[0] = &_absH;
    _reactions[1] = &_addH;
    _reactions[2] = &_formDimer;
    _reactions[3] = &_dropDimer;
    _reactions[4] = &_addCH2;
    _reactions[5] = &_etching;
    _reactions[6] = &_migrationBridge;
    _reactions[7] = &_migrationH;
}

void ReactionsPool::seeAtActives(std::set<Carbon *> activeCarbons) {

    std::cout << "\n (param) Active: " << activeCarbons.size();

    for (Carbon *carbon : activeCarbons) {
        _addH.seeAt(carbon);
        _formDimer.seeAt(carbon, 0);
    }
}

void ReactionsPool::seeAtHydrogens(std::set<Carbon *> hydroCarbons) {

    std::cout << "\n (param) Hydro: " << hydroCarbons.size();

    for (Carbon *carbon : hydroCarbons) {
        _absH.seeAt(carbon);
        //_migrationBridge->seeAt(carbon);
        _etching.seeAt(carbon);
    }
}
void ReactionsPool::seeAtDimer(std::map<Carbon *, Carbon *> dimers) {

    std::cout << "\n (param) Dimers: " << dimers.size();

    for (auto &carbons_pair : dimers) {
        // TODO: стоит пересмотреть метод SeeAt для DualReaction, в плане аргументов (чтобы принмало &pair вместо двух Carbon *)
        _addCH2.seeAt(carbons_pair.first, carbons_pair.second);
        //_dropDimer.seeAt(carbons_pair.first, carbons_pair.second);
        _migrationH.seeAt(carbons_pair.first, carbons_pair.second);
    }
}

float ReactionsPool::doReaction() {

    double commonRates[8] = {
        _addH.commonRate(),
        _absH.commonRate(),
        _addCH2.commonRate(),
        _formDimer.commonRate(),
        _dropDimer.commonRate(),
        _etching.commonRate(),
        _migrationH.commonRate(),
        _migrationBridge.commonRate(),
    };

    std::cout << "\n ---- commonRates ------\n";
    std::cout << "AddHReaction: " << commonRates[0] << "\n";
    std::cout << "AbsHReaction: " << commonRates[1] << "\n";
    std::cout << "AddCH2Reaction: " << commonRates[2] << "\n";
    std::cout << "FormDimerReaction: " << commonRates[3] << "\n";
    std::cout << "DropDimerReaction: " << commonRates[4] << "\n";
    std::cout << "EtchingReaction: " << commonRates[5] << "\n";
    std::cout << "MigrationHReaction: " << commonRates[6] << "\n";
    std::cout << "MigrationBridgeReaction: " << commonRates[7] << "\n";
    std::cout << " -----------------------\n";

    // считаем сумму скоростей во всем реакциям.
    double sumRate = 0.0;

    for (int i = 0; i < 8; i++) sumRate += commonRates[i];

    std::cout << "\n    ...sumRate: " << sumRate << std::endl;

    // нормируем реакции.
    double valuetedRates[8];
    for (int i = 0; i < 8; i++) {
        valuetedRates[i] = commonRates[i] / sumRate;
    }

    // строим линию
    for (int i = 1; i < 8; i++) {
        valuetedRates[i] += valuetedRates[i-1];
    }

    // кидаем случайное число, выбираем реакцию и проводим ее.
    double reactionIndex = rand() / double(RAND_MAX) ;
    double dt = 0;

    std::cout << "\n    ...choose reaction... ";
    if (reactionIndex < valuetedRates[0]) {
        std::cout << "addhreaction!\n";
        _addH.doIt();
        _addH.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[0];
    }
    else if (reactionIndex < valuetedRates[1]) {
        std::cout << "abshreaction!\n";
        _absH.doIt();
        _absH.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[1];
    }
    else if (reactionIndex < valuetedRates[2]) {
        std::cout << "addch2reaction!\n";
        _addCH2.doIt();
        _addCH2.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[2];
    }
    else if (reactionIndex < valuetedRates[3]) {
        std::cout << "formdimer!\n";
        _formDimer.doIt();
        _formDimer.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[3];
    }
    else if (reactionIndex < valuetedRates[4]) {
        std::cout << "dropdimer!\n";
        _dropDimer.doIt();
        _dropDimer.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[4];
    }
    else if(reactionIndex < valuetedRates[5]) {
        std::cout << "etching!\n";
        _etching.doIt();
        _etching.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[5];
    }
    else if (reactionIndex < valuetedRates[6]) {
        std::cout << "migrH!\n";
        _migrationH.doIt();
        _migrationH.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[6];
    }
    else {
        std::cout << "migrBridge!\n";
        _migrationBridge.doIt();
        _migrationBridge.incTimes();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[7];
    }

    std::cout << "\ndt = " << dt << std::endl;
    return dt;
}

void ReactionsPool::reset() {
    for (int i = 0; i < REACTIONS_NUM; i++)
        _reactions[i]->reset();
}

double ReactionsPool::totalRate() {
    // срань comming soon...
}

int *ReactionsPool::reactionTimes() {
    int times[REACTIONS_NUM];

    for (int i = 0; i < REACTIONS_NUM; i++) {
        times[i] = _reactions[i]->times();
        std::cout << "\n" << times[i];
    }
    return times;
}
