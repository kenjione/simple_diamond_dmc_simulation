#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "renderarea.h"
#include "playbutton.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
     explicit MainWindow();
     ~MainWindow();

private:
     RenderArea* renderArea;
     Button* nextButton;
     Button* saveButton;
     Button* restoreButton;
     PlayButton* playButton;
};

#endif // MAINWINDOW_H
