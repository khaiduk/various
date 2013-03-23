#include "treeviewelement.h"
#include <cmath>
#include <iostream>



TreeViewElement::TreeViewElement():
    _depth(0),
    _highlight(TreeViewElement::inactive),
    _currentRect(0,0,0,0),
    _rect(0,0,1,1),
    _parent(NULL),
    _loaded(true)
{
    _element = NULL;
    std::vector<FileSystem::Path> disks = FileSystem::Globals::getDisks();
    for(uint i=0; i<disks.size(); ++i)
    {
        TreeViewElement* e = new TreeViewElement(disks[i], _depth + 1);
        e->_parent = this;
        _contents.push_back(e);
    }
    placeContents();

}

TreeViewElement::TreeViewElement(const FileSystem::Path &path, int depth):
    _depth(depth),
    _highlight(TreeViewElement::inactive),
    _currentRect(0,0,0,0),
    _rect(0,0,1,1),
    _parent(NULL),
    _loaded(false)
{
    if(FileSystem::Globals::whatIs(path) == FileSystem::Globals::dir)
    {
        _element = new FileSystem::Directory(path);
    }
    else
    {
        _element = new FileSystem::File(path);
    }
}

TreeViewElement::~TreeViewElement()
{
    delete _element;
    for(uint i=0; i<_contents.size(); ++i)
    {
        delete _contents[i];
    }
}

void TreeViewElement::draw(QPainter& painter, TreeViewStyle &style, const QRect &rect, const QRect& view, const int depth)
{
    painter.setFont(style.font);
    int fontSize = painter.fontInfo().pixelSize();
    int padding = 4;

    _currentRect.setX(rect.x() + rect.width()*_rect.x() + padding);
    _currentRect.setY(rect.y() + rect.height()*_rect.y() + padding);
    _currentRect.setWidth(rect.width()*_rect.width() - 2 * padding);
    _currentRect.setHeight(rect.height()*_rect.height() - 2 * padding);

    if(_currentRect.width() < 0 || _currentRect.height() < 0) // za ma³y by narysowaæ
        return;

    if(_currentRect.x() + _currentRect.width() < 0 ||
            _currentRect.y() + _currentRect.height() < 0 ||
            _currentRect.x() > view.width() ||
            _currentRect.y() > view.height()) // za daleko by narysowaæ
        return;

    if(!_loaded)
    {
        QtConcurrent::run(this, &TreeViewElement::loadContents);
        _loaded = true;
    }

    switch(_highlight)
    {
    case TreeViewElement::active:   painter.setBrush(style.aktywny); break;
    case TreeViewElement::current:  painter.setBrush(style.wybrany); break;
    case TreeViewElement::selected: painter.setBrush(style.zaznaczony); break;
    case TreeViewElement::inactive:
    default:                        painter.setBrush(style.nieaktywny); break;
    }



    painter.setPen(Qt::black);
    painter.drawRect(_currentRect);

    if(_element)
        painter.drawText(_currentRect, Qt::AlignTop | Qt::AlignHCenter, QString::fromStdString(_element->getName()));

    QRect contentRect;
    contentRect.setX(_currentRect.x() + padding);
    contentRect.setY(_currentRect.y() + fontSize + padding);
    contentRect.setWidth(_currentRect.width() - 2*padding);
    contentRect.setHeight(_currentRect.height() - 2*padding - fontSize);

    for(uint i=0;i<_contents.size();i++)
    {
        _contents[i]->draw(painter, style, contentRect, view, depth - 1);
    }
}

void TreeViewElement::setHighlight(TreeViewElement::HighlightStyle hightlight)
{
    _highlight = hightlight;
}

void TreeViewElement::resetHighlight()
{
    _highlight = TreeViewElement::inactive;
}

TreeViewElement* TreeViewElement::getUnder(QPoint p, int depth)
{
    TreeViewElement* ret = NULL;

    if(depth < 0)
        return NULL;

    if( ! _currentRect.contains(p) || _currentRect.width() < 0 || _currentRect.height() < 0)
        return NULL;


    for(uint i=0;i<_contents.size();i++)
    {
        ret = _contents[i]->getUnder(p, depth - 1);
        if(ret != NULL)
            return ret;
    }

    if(ret == NULL)
    {
        ret = this;
    }

    return ret;

}

TreeViewElement *TreeViewElement::getSub(FileSystem::Path path)
{
    if(!_loaded)
    {
        loadContents();
    }

    std::string pathstr = QString::fromStdString(path.getPath()).replace('\\', '/').toStdString();

    if(_element && QString::fromStdString(_element->getPath()).replace('\\', '/').toStdString() == pathstr)
        return this;

    TreeViewElement* ret = NULL;
    for(uint i=0;i<_contents.size();i++)
    {
        std::string dirstr = QString::fromStdString(_contents[i]->_element->getPath().getPath()).replace('\\', '/').toStdString();
        if(pathstr.find(dirstr) != std::string::npos)
        {
            ret = _contents[i]->getSub(path);
        }
    }

    return ret;
}

FileSystem::Path TreeViewElement::getPath()
{
    if(_element)
        return _element->getPath();
    else
        return FileSystem::Path();
}

QRect TreeViewElement::getCurrentRect()
{
    return _currentRect;
}

TreeViewElement *TreeViewElement::getParent()
{
    return _parent;
}

void TreeViewElement::fillToRect(QRectF &root, const QRect &view) const
{
    QRectF pos = _rect;
    for(TreeViewElement* elem = _parent; elem != NULL; elem = elem->_parent)
    {
        pos.setRect(pos.x() * elem->_rect.width() + elem->_rect.x(),
                    pos.y() * elem->_rect.height() + elem->_rect.y(),
                    pos.width() * elem->_rect.width(),
                    pos.height() * elem->_rect.height());
    }

    root.setRect(-1.0 * pos.x() / pos.width() * view.width(),
                 -1.0 * pos.y() / pos.height() * view.height(),
                 1.0 / pos.width() * view.width(),
                 1.0 / pos.height() * view.height());
}

void TreeViewElement::loadContents()
{
    if(!_element)
        return;

    if(_element->whatIs() == FileSystem::Globals::dir)
    {
        FileSystem::Directory dir = static_cast<FileSystem::Directory>(*_element);
        vector<FileSystem::Element> contents;

        try{
            contents = dir.content();
        }catch(...)
        {
        }

        _contents.clear();

        for(uint i=0; i<contents.size(); ++i)
        {
            FileSystem::Element element = contents[i];
            TreeViewElement* e = new TreeViewElement(element.getPath(), _depth + 1);
            e->_parent = this;
            _contents.push_back(e);
        }
        placeContents();
    }
    _loaded = true;
}

void TreeViewElement::placeContents()
{
    int n = _contents.size();
    if(n == 0)
        return;
    int cols = sqrt(n * _rect.width() / _rect.height());
    if(cols >= n) cols = n;
    if(cols <= 0) cols = 1;
    int rows = n/cols;
    int rest = n - rows*cols;
    double ratio = 1.0 * cols * rows / n;

    if(ratio > 0.9 && rest > 0)
        ratio = 0.9;

    int i=0;

    if(_depth % 2 != 0)
    {
        for(int x=0;x<rows;++x)
        {
            for(int y=0;y<cols;++y)
            {
                _contents[i++]->_rect = QRectF(1.0/rows * ratio * x, 1.0/cols * y, ratio / rows, 1.0/cols);
            }
        }

        for(int y=0;y<rest;++y)
        {
            _contents[i++]->_rect = QRectF(ratio, 1.0/rest * y, 1 - ratio, 1.0/rest);
        }
    }
    else
    {
        for(int y=0;y<rows;++y)
        {
            for(int x=0;x<cols;++x)
            {
                _contents[i++]->_rect = QRectF(1.0/cols * x, 1.0/rows * ratio * y, 1.0/cols, ratio / rows);
            }
        }

        for(int x=0;x<rest;++x)
        {
            _contents[i++]->_rect = QRectF(1.0/rest * x, ratio, 1.0/rest, 1 - ratio);
        }
    }
}
