#include "formdimerreaction.h"

FormDimerReaction::FormDimerReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface), _crystal(crystal) {}

void FormDimerReaction::operator() (Carbon *first, Carbon *second) {
    if (_pairs.find(second) == _pairs.end()) { // корявая проверка на наличие.
        _sites.push_back(first);               // Если find не находит он же выставляет указатель на end()?
        _pairs.insert(second);
    }
}

void FormDimerReaction::seeAt(Carbon *carbon) {
    _crystal->posDimerIter(carbon, ref(*this));
}

void FormDimerReaction::doIt() {

}

void FormDimerReaction::reset() {
    MonoReaction::reset();
    _pairs.clear();
}
