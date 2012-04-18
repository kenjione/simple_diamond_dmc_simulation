#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include "button.h"

class PlayButton : public Button
{
    Q_OBJECT
public:
    explicit PlayButton(const QString& start_text, const QString& stop_text, QWidget *parent = 0);

signals:
    void timerStart();
    void timerStop();

private slots:
    void changeState();

private:
    QString start_text, stop_text;
    bool started;
};

#endif // PLAYBUTTON_H
