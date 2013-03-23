#include "treeview.h"
#include <iostream>
#include "FileSystem/Directory.h"

TreeView::TreeView(QWidget *parent) :
    QWidget(parent),
    _currentlySelecting(false),
    _root(NULL),
    _current(NULL),
    _style(QFont(), Qt::white, Qt::blue, Qt::gray , Qt::green)
{
    _rootRect = QRect(0, 0, 0, 0);
    setMouseTracking(true);
    _active = NULL;
}

TreeView::~TreeView()
{
    if(_root != NULL)
        delete _root;
}

void TreeView::setDirectory(FileSystem::Path dir)
{
    if(!_root)
    {
        _current = _root = new TreeViewElement();
    }

    if(_current->getPath() != dir)
    {
        TreeViewElement* tmp = _root->getSub(dir);
        if(tmp == NULL)
            _current = _root;
        else
            _current = tmp;

        _current->fillToRect(_rootRect, rect());
        emit directoryChanged(dir);
    }
    else
    {
        _current->loadContents();//refresh
    }
}

void TreeView::setStyle(const TreeViewStyle &style)
{
    _style = style;
}

void TreeView::paintEvent(QPaintEvent *event)
{
    if(_rootRect.width() == 0)
    {
        _rootRect = rect();
    }
    QPainter painter(this);

    if(_active != NULL)
        _active->setHighlight(TreeViewElement::active);
    if(_current != NULL)
        _current->setHighlight(TreeViewElement::current);
    for(std::set<TreeViewElement*>::iterator it = _selected.begin(); it != _selected.end() ;++it)
    {
        (*it)->setHighlight(TreeViewElement::selected);
    }

    if(_root != NULL)
        _root->draw(painter, _style, _rootRect.toRect(), rect(), 5);

    if(_active != NULL)
        _active->resetHighlight();
    if(_current != NULL)
        _current->resetHighlight();
    for(std::set<TreeViewElement*>::iterator it = _selected.begin(); it != _selected.end() ;++it)
    {
        (*it)->resetHighlight();
    }

    if(_currentlySelecting)
    {
        painter.setBrush(Qt::transparent);
        painter.setPen(QPen(Qt::lightGray, 5.0));
        painter.drawPath(_selectionPath);
    }
}

void TreeView::wheelEvent(QWheelEvent *event)
{
    if(_currentlySelecting)
        return;

    double delta = event->delta()/1200.0 + 1;
    QPointF topLeft = (_rootRect.topLeft() - event->pos())*delta + event->pos();
    QPointF bottomRight = (_rootRect.bottomRight() - event->pos())*delta + event->pos();
    _rootRect.setTopLeft(topLeft);
    _rootRect.setBottomRight(bottomRight);
    updateCurrentElement();
    update();
}

void TreeView::mouseMoveEvent(QMouseEvent *event)
{
    if(_currentlySelecting)
    {
        _active = NULL;
        _selectionPath.lineTo(event->posF());
        TreeViewElement* obj =  _current->getUnder(event->pos(), 1);
        if( obj != NULL && obj != _current )
            _selected.insert( obj );
        update();
        return;
    }
    if(event->buttons() & Qt::RightButton)
    {
        _rootRect.translate(event->pos() - prevpos);
        updateCurrentElement();
    }

    _active = _current->getUnder(event->pos(), 1);

    prevpos = event->pos();
    update();
}

void TreeView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _currentlySelecting = true;
        _selectionPath = QPainterPath(event->posF());
        _selected.clear();
    }
}

void TreeView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _currentlySelecting = false;
        std::vector<FileSystem::Path> ret;
        for(std::set<TreeViewElement*>::iterator it = _selected.begin(); it != _selected.end() ;++it)
        {
            ret.push_back((*it)->getPath());
        }

        emit selectedElements(ret);
    }
}

void TreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        TreeViewElement* obj = _current->getUnder(prevpos, 1);
        if(obj == NULL)
            return;
        if(FileSystem::Globals::whatIs(obj->getPath()) == FileSystem::Globals::dir)
        {
            setDirectory(obj->getPath());
        }
        else
        {
            emit openFile(obj->getPath());
        }
    }
    else if(event->buttons() & Qt::RightButton)
    {
        if(_current->getParent() != NULL)
        {
            if(_current->getParent() == _root)
            {
                _current = _root;
                _current->fillToRect(_rootRect, rect());
            }
            else
            {
                setDirectory(_current->getParent()->getPath());
            }
        }
    }
    update();
}

void TreeView::updateCurrentElement()
{
    // sprawdz jak daleko oddalilismy sie wzgledem biezacego:
    QRect intersection = _current->getCurrentRect().intersected(rect());

    if( ( 1.0 *(intersection.width()*intersection.height()) /
          (rect().width()*rect().height()) ) < 0.6 ) // mniej ni¿ 60%
    {
        if(_current->getParent() != NULL)
        {
            _current = _current->getParent(); // poziom wy¿ej
            emit directoryChanged(_current->getPath());
        }
    }
    else
    {
        if(_current->getUnder(prevpos, 1) != NULL)
        {
            intersection = _current->getUnder(prevpos, 1)->getCurrentRect().intersected(rect());
            if( ( 1.0 *(intersection.width()*intersection.height()) /
                  (rect().width()*rect().height()) ) > 0.61 ) // wiêcej ni¿ 61%
            {
                if(FileSystem::Globals::whatIs(_current->getUnder(prevpos, 1)->getPath()) == FileSystem::Globals::dir)
                {
                    _current = _current->getUnder(prevpos, 1); // poziom ni¿ej
                    emit directoryChanged(_current->getPath());
                }
            }
        }
    }
}
