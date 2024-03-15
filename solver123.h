#ifndef SOLVER123_H
#define SOLVER123_H

#include <QDialog>

namespace Ui {
class Solver123;
}

class Solver123 : public QDialog
{
    Q_OBJECT

public:
    explicit Solver123(QWidget *parent = nullptr);
    ~Solver123();

    void currentAmountChanger();
    void addRangeButton_clicked();
    void deleteRangeButton_clicked();
    void calculator(int row, int column);
    float probabilityCalc(float range_start, float range_end, int amount_of_failed_products);
private:
    int starting_amount;
    Ui::Solver123 *ui;
};

#endif // SOLVER123_H
