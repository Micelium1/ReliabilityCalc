#ifndef SOLVER6_H
#define SOLVER6_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Solver6;
}

class Solver6 : public QDialog
{
    Q_OBJECT

public:
    explicit Solver6(QWidget *parent = nullptr);
    ~Solver6();

    void addRangeButton_clicked();
    void deleteRangeButton_clicked();
    void calculator(int row, int column);
private:
    QVector<float> Average;
    QVector<float> Amounts;
    Ui::Solver6 *ui;
};

#endif // SOLVER6_H
