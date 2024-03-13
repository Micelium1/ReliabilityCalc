#ifndef SOLVER6_H
#define SOLVER6_H

#include <QDialog>

namespace Ui {
class Solver6;
}

class Solver6 : public QDialog
{
    Q_OBJECT

public:
    explicit Solver6(QWidget *parent = nullptr);
    ~Solver6();

private:
    Ui::Solver6 *ui;
};

#endif // SOLVER6_H
