#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow() {
//   renderArea = new RenderArea(this);
//   nextButton = new Button("Next", this);
//   saveButton = new Button("Save", this);
//   restoreButton = new Button("Restore", this);
//   playButton = new PlayButton("Play", "Stop", this);

//   connect(nextButton, SIGNAL(clicked()), renderArea, SLOT(next()));
//   connect(saveButton, SIGNAL(clicked()), renderArea, SLOT(save()));
//   connect(restoreButton, SIGNAL(clicked()), renderArea, SLOT(restore()));
//   connect(playButton, SIGNAL(timerStart()), renderArea, SLOT(play()));
//   connect(playButton, SIGNAL(timerStop()), renderArea, SLOT(stop()));

//   QHBoxLayout *buttonsLayout = new QHBoxLayout;
//   buttonsLayout->addWidget(nextButton);
//   buttonsLayout->addWidget(saveButton);
//   buttonsLayout->addWidget(restoreButton);
//   buttonsLayout->addWidget(playButton);
//   QGroupBox *buttonsGroup = new QGroupBox;
//   buttonsGroup->setLayout(buttonsLayout);

//   QVBoxLayout *mainLayout = new QVBoxLayout(this);
//   mainLayout->addWidget(renderArea);
//   mainLayout->addWidget(buttonsGroup);

   setWindowTitle("Dynamic Monte Carlo Simulation of Chemical Vapor Deposition");
}

MainWindow::~MainWindow() {
//    delete renderArea;
//    delete nextButton;
//    delete playButton;
}
