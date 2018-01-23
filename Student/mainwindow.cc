#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "starsystem.hh"
#include "highscorelist.hh"
#include "ioexception.hh"

#include <cassert>
#include <memory>
#include <iostream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), highscorelist_("Assets/highscore.txt", 10) {
    ui->setupUi(this);

    connect(ui->button_quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->button_nextTurn, SIGNAL(clicked()), this, SLOT(nextTurn()));
    connect(ui->button_instructions, SIGNAL(clicked()), this, SLOT(openInstructions()));
    connect(ui->button_repair, SIGNAL(clicked()), this, SLOT(fixPlayerShip()));
    connect(ui->button_highscore, SIGNAL(clicked()), this, SLOT(openHighScore()));

    turncount_ = 0;    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatistics(std::shared_ptr<Student::Statistics> statistics) {
    statistics_ = statistics;
}

void MainWindow::setEventHandler(std::shared_ptr<Student::EventHandler> eventhandler) {    
    eventhandler->setStatusBar(ui->statusbar);
}


void MainWindow::openInstructions() const {
    InstructionsDialog instr;
    instr.exec();
}


void MainWindow::nextTurn() {
    assert(gamerunner_);
    assert(playership_);
    assert(statistics_);
    //std::cout << "== Turn " << turncount_ << " ==" << std::endl;
    gamerunner_->createActions();
    gamerunner_->doActions();
    ++turncount_;
    ui->label_turncounter->setText(QString("Turn: %1").arg(turncount_));    
    refreshStats();
    centerOnPlayer();
    ui->mapview->scene()->update();

    if (playership_->getEngine()->isBroken()) {

        if (statistics_->getCreditBalance() >= REPAIRPRICE_) {
            ui->button_repair->setEnabled(true);
        } else {
            gameOver();  // Not enough money to fix broken engine
        }
    } else {
        ui->button_repair->setEnabled(false);
    }
}

void MainWindow::fixPlayerShip() {
    assert(playership_);
    assert(statistics_);
    playership_->getEngine()->repair(playership_->getEngine()->getMaxHealth());
    statistics_->reduceCredits(REPAIRPRICE_);
    nextTurn();
}

void MainWindow::openHighScore() {
    QMessageBox highscorebox;
    std::string highscoremessage;
    int i = 1;
    for (auto line: highscorelist_.getScoreList()) {
        highscoremessage += std::to_string(i) + ". " + line.name + " " + std::to_string(line.score) + "\n";
        ++i;
    }
    highscorebox.setText("High scores:");
    highscorebox.setInformativeText(QString::fromStdString(highscoremessage));
    highscorebox.exec();
}

void MainWindow::centerOnPlayer() {    
    ui->mapview->centerOn(galaxymap_->getShipLocation(playership_));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->ignore(); // Stop closing the main window by ignoring the event.

    // Draw a confirmation dialog. If the user clicks "Yes", accept the event and close the main window.
    if (QMessageBox::Yes == QMessageBox::question(this, "Quit", "Do you really want to quit?", QMessageBox::Yes | QMessageBox::No))  {
        event->accept();
    }

}

void MainWindow::gameOver() {
    ui->button_nextTurn->setEnabled(false);

    QMessageBox gameoverbox;
    gameoverbox.setText("GAME OVER");
    gameoverbox.setInformativeText("You don't have enough money to repair your engine.");
    gameoverbox.exec();

    int points = statistics_->getPoints();
    if (highscorelist_.isHighScore(points)) {
        QString highscorename = QInputDialog::getText(this, "New high score!", "Your name:", QLineEdit::Normal);
        highscorelist_.addScore(points, highscorename.toStdString());
        try {
            highscorelist_.saveScore();
        } catch (const Common::IoException &e) {
            QMessageBox::critical(this, "Could not write high scores", QString::fromStdString(e.msg()));
        }
    }
}

void MainWindow::refreshStats() {
    assert(statistics_);
    ui->label_savedships->setText(QString("Ships robbed: %1").arg(statistics_->getSavedShips()));
    ui->label_lostships->setText(QString("Ships lost: %1").arg(statistics_->getLostShips()));
    ui->label_credits->setText(QString("Credits: %1").arg(statistics_->getCreditBalance()));
    ui->label_points->setText(QString("Points: %1").arg(statistics_->getPoints()));
}

void MainWindow::setGalaxyMap(std::shared_ptr<Student::GalaxyMap> galaxymap) {
    galaxymap_ = galaxymap;
    ui->mapview->setScene(galaxymap->getScene());
}


void MainWindow::setGameRunner(std::shared_ptr<Common::IGameRunner> gameRunner) {
    gamerunner_ = gameRunner;
}

void MainWindow::setPlayerShip(std::shared_ptr<Student::PlayerShip> playership) {
    playership_ = playership;
    centerOnPlayer();
}

void MainWindow::setPlayerEngine(std::shared_ptr<Student::WarpDrivePlusPlus> engine) {
    engine->setStatusbar(ui->statusbar);
}
