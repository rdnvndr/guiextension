#pragma once

#include "guiextensionglobal.h"

#include <QtWidgets/QComboBox>

class QTreeView;

namespace RTPTechGroup {
namespace Widgets {

//! ComboxBox с выпадающим списком в виде QTreeView
/*! Класс предназначен для выбора значения ComboBox
    из древовидной модели.
    \n
    Пример: \n
    \code
    TreeComboBox *comboBoxLinkAttr;
    comboBoxLinkAttr = new TreeComboBox();
    comboBoxLinkAttr->setModel(classFilterModel);
    \endcode
*/

class GUIEXTENSIONLIB TreeComboBox : public QComboBox
{
public:
    //! Конструктор класса
    explicit TreeComboBox(QWidget *parent = nullptr);

    //! Деструктор класса
    virtual ~TreeComboBox();

    //! Устанавливает модель для списка
    /*!
       \param model Модель
    */
    void setModel(QAbstractItemModel *model);

    //! Устанавливает текущий индекс модели списка
    /*!
       \param index Индекс
    */
    void setCurrentModelIndex (const QModelIndex &index);

    //! Возвращает текущий индекс модели списка
    /*!
       \return Индекс
    */
    QModelIndex currentModelIndex();

    //! Событие для перерисовки
    /*!
       \brief paintEvent
    */
    void paintEvent(QPaintEvent *event);

    //! Устанавливает текст по умолчанию
    /*!
       \param text Текст по умолчанию
    */
    void setDisplayText(const QString &text);

    //! Получение текста по умолчанию
    /*!
       \return Текст по умолчанию
    */
    QString displayText() const;

    //! Устанавливает иконку по умолчанию
    /*!
       \param icon"> иконка
    */
    void setDisplayIcon(const QIcon &icon);

    //! Получение иконки по умолчанию
    /*!
       \return Иконка
    */
    QIcon displayIcon() const;

    //! Устанавливает колонку со значением
    /*!
       \param column Колонка
    */
    void setIndexColumn(int column);

    //! Устанавливает колонку для отображения
    /*!
       \param column Колонка
    */
    void setShowingColumn(int column);

    //! Устанавливает режим показа иконки
    /*!
       \param showing Режим отображения иконки
    */
    void setShowingIcon(bool showing);

    //! Получение режима показа иконки
    /*!
       \return Режим отображения иконки
    */
    bool showingIcon();

    //! Устанавливает корневой индекс
    /*!
       \param index Индекс
    */
    void setRootModelIndex(const QModelIndex &index);

    //! Получение корневого индекса
    /*!
       \return Индекс
    */
    QModelIndex rootModelIndex();

    //! Показывает выпадающий список в виде дерева
    void showPopup();

    //! Скрывает выпадающий список в виде дерева
    void hidePopup();

protected:
    //! Фильтр событий
    /*!
        \param object Объект
        \param event Событие
    */
    bool eventFilter(QObject *object, QEvent *event);

private:
    //! Флаг пропуска показа списка
    bool _skipNextHide;

    //! Древовидный список
    QTreeView *_treeView;

    //! Текст по умолчанию
    QString _displayText;

    //! Иконка по умолчанию
    QIcon _displayIcon;

    //! Режим показа иконки
    bool _showingIcon;

    //! Колонка с отображаемым значением
    int _showingColumn;

    //! Колонка со значением
    int _indexColumn;

    //! Корневой индекс
    QModelIndex _rootIndex;
};

}}
