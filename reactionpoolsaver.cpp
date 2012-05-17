#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(char *outFileName, ReactionsPool *reactionPool) :
    Saver(outFileName), _reactionPool(reactionPool) {
        _outFile.open(outFileName, std::ios_base::out);
        //if (_outFile == NULL) std::cout << "    ...file not created..\n"; else std::cout << "   ...file created!\n"; //
}

void ReactionPoolSaver::save() {
    _outFile << "[reaction#] = [times]\n";

    for (int i = 0; i < REACTIONS_NUM; i++)
    {
        _outFile << "reaction #" << i+1 <<  " = " << _reactionPool->reactionTimes()[i] << std::endl;
    }
}
