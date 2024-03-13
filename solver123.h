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

private:
    Ui::Solver123 *ui;
};

#endif // SOLVER123_H
