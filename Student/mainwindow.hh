#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "instructionsdialog.hh"
#include "highscorelist.hh"
#include "statistics.hh"
#include "eventhandler.hh"
#include "igamerunner.hh"
#include "galaxy.hh"
#include "galaxymap.hh"
#include "warpdriveplusplus.hh"

#include <QMainWindow>
#include <QDialog>
#include <memory>
#include <QGraphicsScene>

namespace Ui {
    class MainWindow;
}

/*!
 * \brief The MainWindow class
 * \author Juha Suvanto
 *
 * Displays the main game window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow Default constructor for the main window.
     * \param parent The parent window.
     */
    explicit MainWindow(QWidget *parent = 0);

    /*!
     *\ brief MainWindow Default deconstructor.
     */
    ~MainWindow();

    /*!
     * \brief setStatsPointer Sets the statistics object so statistics can be shown in main window.
     * \param stats_pointer The statistics object.
     */
    void setStatistics(std::shared_ptr<Student::Statistics> statistics);

    /*!
     * \brief setEventHandler Tells event handler which statusbar to use.
     * \param eventhandler The event handler.
     */
    void setEventHandler(std::shared_ptr<Student::EventHandler> eventhandler);

    /*!
     * \brief setGalaxyMap Sets the galaxy map to display in the UI.
     * \param galaxymap Pointer to the galaxy map.
     */
    void setGalaxyMap(std::shared_ptr<Student::GalaxyMap> galaxymap);

    /*!
     * \brief setGameRunner Sets the game runner so the Next Turn button works.
     * \param gameRunner A pointer to the game runner.
     */
    void setGameRunner(std::shared_ptr<Common::IGameRunner> gameRunner);

    /*!
     * \brief setPlayerShip Sets the player ship so we can repair it.
     * \param playership A pointer to the player ship.
     */
    void setPlayerShip(std::shared_ptr<Student::PlayerShip> playership);

    /*!
     * \brief setPlayerEngine Tells the player ship's engine the pointer to statusbar.
     * \param engine The player ship's engine.
     */
    void setPlayerEngine(std::shared_ptr<Student::WarpDrivePlusPlus> engine);


public slots:

    /*!
     * \brief openInstructions Opens the instructions dialog.
     */
    void openInstructions() const;

    /*!
     * \brief nextTurn Advances the game by one turn.
     * \pre Game runner, player ship and statistics object have been set.
     */
    void nextTurn();

    /*!
     * \brief fixPlayerShip Fixes the player ship's engine and deducts REPAIRPRICE_ credits.
     * \pre Player ship and statistics object have been set.
     */
    void fixPlayerShip();

    /*!
     * \brief openHighScore Opens the High Score list.
     */
    void openHighScore();

private:

    /*!
     * \brief ui Points to the main window.
     */
    Ui::MainWindow *ui;

    /*!
     * \brief refreshStats Refreshes the statistics in the main window.
     * \pre Statistics object has been set.
     */
    void refreshStats();

    /*!
     * \brief stats_pointer_ Points to the player statistics object.
     */
    std::shared_ptr<Student::Statistics> statistics_;

    /*!
     * \brief gamerunner_ Points to the game runner.
     */
    std::shared_ptr<Common::IGameRunner> gamerunner_;

    /*!
     * \brief MainWindow::closeEvent Pops up a confirmation dialog when trying to quit the program.
     * \param event The close event.
     */
    void closeEvent(QCloseEvent *event);

    /*!
     * \brief galaxymap_ The galaxy map to display in the UI.
     */
    std::shared_ptr<Student::GalaxyMap> galaxymap_;

    /*!
     * \brief turncount_ The turn counter.
     */
    unsigned int turncount_;

    /*!
     * \brief playership_ Points to the player's ship.
     */
    std::shared_ptr<Student::PlayerShip> playership_;

    /*!
     * \brief REPAIRPRICE_ The cost of repairing the player's ship's engine.
     */
    const int REPAIRPRICE_ = 1000;

    /*!
     * \brief gameOver Ends the game. Shows a game over message box and disables the next turn button.
     */
    void gameOver();

    /*!
     * \brief centerOnPlayer Centers the galaxy map view on the player ship.
     * \pre Player ship and galaxy map have been set.
     */
    void centerOnPlayer();

    Student::HighScoreList highscorelist_;
};

#endif // MAINWINDOW_HH
