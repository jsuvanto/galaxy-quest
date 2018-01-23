#include <QString>
#include <QtTest>
#include "statistics.hh"
#include "gameexception.hh"
class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:

    void testSavingShips();
    void testLosingShips();
    void testPoints();
    void testCredits();
};

/**
 * @brief StatisticsTest::StatisticsTest tests the initial values of the Statistics class.
 */
StatisticsTest::StatisticsTest() {
    Student::Statistics test_stats;
    // All values should be set to zero when initialising the class.
    QCOMPARE(test_stats.getSavedShips(), 0u);
    QCOMPARE(test_stats.getLostShips(), 0u);
    QCOMPARE(test_stats.getPoints(), 0u);
    QCOMPARE(test_stats.getCreditBalance(), 0);
}

/**
 * @brief StatisticsTest::testSavingShips tests adding a saved ship and returning the number of saved ships.
 */
void StatisticsTest::testSavingShips() {
    Student::Statistics test_stats;
    test_stats.addSavedShip();                  // Add a saved ship.
    QCOMPARE(test_stats.getSavedShips(), 1u);   // There should only be one saved ship.
}

/**
 * @brief StatisticsTest::testLosingShips tests adding a lost ship and returning the number of lost ships.
 */
void StatisticsTest::testLosingShips() {
    Student::Statistics test_stats;
    test_stats.addLostShip();                   // Add a ship.
    QCOMPARE(test_stats.getLostShips(), 1u);    // There should only be one lost ship.
}

/**
 * @brief StatisticsTest::testPoints tests adding, reducing and returning the player's points.
 */
void StatisticsTest::testPoints() {
    Student::Statistics test_stats;

    test_stats.addPoints(100);              // Add 100 points.
    QCOMPARE(test_stats.getPoints(), 100u); // Player should have 100 points.

    test_stats.reducePoints(80);            // Reduce 80 points.
    QCOMPARE(test_stats.getPoints(), 20u);  // Player should have 20 points.

    test_stats.reducePoints(50);            // Try to reduce points below 0. This should set points to 0.
    QVERIFY2(test_stats.getPoints() == 0, "Error when trying to reduce points to below 0.");

    test_stats.addPoints(50);               // Give 50 points.
    QCOMPARE(test_stats.getPoints(), 50u);  // Player should have 50 points.
    test_stats.reducePoints(50);            // Remove 50 points.
    QCOMPARE(test_stats.getPoints(), 0u);   // Player should have 0 points.
    test_stats.reduceCredits(0);            // Remove 0 points.
    QCOMPARE(test_stats.getPoints(), 0u);   // Player should have 0 points.
    test_stats.reducePoints(100);           // Try to remove 100 points.
    QCOMPARE(test_stats.getPoints(), 0u);   // Player should still have 0 points.
}


void StatisticsTest::testCredits() {
    Student::Statistics test_stats;

    test_stats.addCredits(1000); // Add 1000 credits.
    QCOMPARE(test_stats.getCreditBalance(), 1000); // There should be 1000 credits on the player's account.

    test_stats.reduceCredits(500); // Reduce 500 credits.
    QCOMPARE(test_stats.getCreditBalance(), 500); // There should be 500 credits on the player's account.

    QVERIFY_EXCEPTION_THROWN(test_stats.reduceCredits(1000), Common::GameException); // Try to reduce 1000 credits which would make the balance go negative.
    QCOMPARE(test_stats.getCreditBalance(), 500); // Balance should be 500 since nothing was reduced.
}


QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
