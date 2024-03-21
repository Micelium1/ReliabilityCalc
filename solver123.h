#ifndef SOLVER123_H
#define SOLVER123_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Solver123;
}

class Solver123 : public QDialog
{
    Q_OBJECT

public:
    explicit Solver123(QWidget *parent = nullptr);
    ~Solver123();

    void startingAmountChanger();
    void addRangeButton_clicked();
    void deleteRangeButton_clicked();
    void calculator(int row, int column);
    float probabilityCalc(int row);
    float failureRateCalc(int row);
    float frequencyEstimation(int row);
private:
    float starting_amount;
    QVector<float> failedProducts;
    Ui::Solver123 *ui;
};

#endif // SOLVER123_H
