#include "playbutton.h"

PlayButton::PlayButton(const QString& start_text, const QString& stop_text, QWidget *parent) :
    Button(start_text, parent), start_text(start_text), stop_text(stop_text), started(false)
{
    connect(this, SIGNAL(clicked()), this, SLOT(changeState()));
}

void PlayButton::changeState() {
    started = !started;
    setText(started ? stop_text : start_text);
    if (started) emit timerStart();
    else emit timerStop();
}
