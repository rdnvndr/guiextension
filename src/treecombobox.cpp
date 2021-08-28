#include "treecombobox.h"

#include <QEvent>
#include <QMouseEvent>
#include <QHeaderView>
#include <QStylePainter>
#include <QtWidgets/QTreeView>

namespace RTPTechGroup {
namespace Widgets {

TreeComboBox::TreeComboBox(QWidget *parent) : QComboBox(parent), _skipNextHide(false)
{
    _rootIndex = QModelIndex();
    QComboBox::resize(250, 30);

    _treeView = new QTreeView();
    _treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(_treeView, &QTreeView::expanded, this, [this](const QModelIndex &index) {
        _treeView->header()->setStretchLastSection(false);
        _treeView->resizeColumnToContents(_showingColumn);
        if (_treeView->header()->width() > _treeView->header()->sectionSize(_showingColumn))
            _treeView->header()->setStretchLastSection(true);

    });
    setView(_treeView);

    view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view()->setAutoScroll(false);
    view()->viewport()->installEventFilter(this);
    view()->setProperty("headerHidden", true);
    view()->setMinimumSize(0, 150);

    _showingColumn = 0;
    _indexColumn = 0;
    _showingIcon = false;
    _displayText = currentText();
}

TreeComboBox::~TreeComboBox()
{
    delete _treeView;
}

bool TreeComboBox::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && object == view()->viewport())
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QModelIndex index = view()->indexAt(mouseEvent->pos());
        if(!view()->visualRect(index).contains(mouseEvent->pos()))
            _skipNextHide = true;
    }
    return false;
}

void TreeComboBox::showPopup()
{
    QComboBox::showPopup();

    _treeView->header()->setStretchLastSection(false);
    _treeView->resizeColumnToContents(_showingColumn);
    if (_treeView->header()->width() > _treeView->header()->sectionSize(_showingColumn))
        _treeView->header()->setStretchLastSection(true);
}

void TreeComboBox::hidePopup()
{
    QComboBox::setRootModelIndex(view()->currentIndex().parent());
    setCurrentIndex(view()->currentIndex().row());

    if(_skipNextHide)
        _skipNextHide = false;
    else {
        QComboBox::hidePopup();
        _displayText = _treeView->currentIndex().data().toString();
        _displayIcon = _treeView->currentIndex().data(Qt::DecorationRole).value<QIcon>();
        setCurrentText(_displayText);
    }

    view()->setRootIndex(_rootIndex);
}

void TreeComboBox::setModel(QAbstractItemModel *model)
{
    QComboBox::setModel(model);
    setShowingColumn(0);

    _treeView->header()->setStretchLastSection(false);
}

void TreeComboBox::setCurrentModelIndex(const QModelIndex &index)
{
    _treeView->setCurrentIndex(index);
    hidePopup();
}

QModelIndex TreeComboBox::currentModelIndex()
{
    QModelIndex index = _treeView->currentIndex();
    return index.sibling(index.row(), _indexColumn);
}

void TreeComboBox::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));
    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    opt.currentText = _displayText;
    if (!_showingIcon)
        opt.currentIcon = QIcon();
    else
        opt.currentIcon = _displayIcon;

    painter.drawComplexControl(QStyle::CC_ComboBox, opt);
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}


void TreeComboBox::setDisplayText(const QString &text)
{
    _displayText = text;
    this->repaint();
}

QString TreeComboBox::displayText() const
{
    return _displayText;
}

void TreeComboBox::setDisplayIcon(const QIcon &icon)
{
    _displayIcon = icon;
}

QIcon TreeComboBox::displayIcon() const
{
    return _displayIcon;
}

void TreeComboBox::setIndexColumn(int column)
{
    _indexColumn = column;
}

void TreeComboBox::setShowingColumn(int column)
{
    _showingColumn = column;
    for (auto i = _treeView->header()->count() - 1; i >= 0; --i)
    {
        if (i != _showingColumn)
            _treeView->hideColumn(i);
        else
            _treeView->showColumn(i);
    }
}

void TreeComboBox::setShowingIcon(bool showing)
{
    _showingIcon = showing;
}

bool TreeComboBox::showingIcon()
{
    return _showingIcon;
}

void TreeComboBox::setRootModelIndex(const QModelIndex &index)
{
    _rootIndex = index;
}

QModelIndex TreeComboBox::rootModelIndex()
{
    return _rootIndex;
}

}}
