#ifndef PKMN_MOVE_PICKER_VIEW
#define PKMN_MOVE_PICKER_VIEW

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class PkmnMovePickerView : public QWidget {

  Q_OBJECT

public:

  explicit PkmnMovePickerView(QWidget *parent = 0);

  void setChangingMove (int);

signals:

  void moveSelected(int, int);

public slots:

  void foo ();

private slots:

  void manageButtonClicked(int);

private:

  int _whichMove;

  QPushButton *_moveList[166];
  QVBoxLayout *_layout;

};

#endif // PKMN_MOVE_PICKER_VIEW
