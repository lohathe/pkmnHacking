#ifndef PKMN_MOVE_PICKER_VIEW
#define PKMN_MOVE_PICKER_VIEW

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>

#include "pkmnelementpickerview.h"
#include "pkmnlistitemview.h"

class PkmnMovePickerView : public QWidget {

  Q_OBJECT

public:

  explicit PkmnMovePickerView(QWidget *parent = 0);

signals:

  void moveSelected(int);

private slots:

  void manageButtonClicked(int);
  void manageFilter(int);
  void manageSort(int);

private:

  PkmnElementPickerView *_elementPicker;
  QRadioButton *_order[2];

  int _element;
  int _sorting;
  void manageSortOrFilter();

  PkmnMoveListItem *_moveList[166];
  QGridLayout *_layout;

};

#endif // PKMN_MOVE_PICKER_VIEW
