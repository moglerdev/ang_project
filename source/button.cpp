#include "button.h"

Button::Button(const QPoint& size, const QString& textContent, const QColor& textColor, const QBrush& background)
{
	QRect rect = QRect(0, 0, size.x(), size.y());

	backgroundItem = new QGraphicsRectItem(rect);
	textItem = new QGraphicsTextItem(textContent);

	addToGroup(backgroundItem);
	addToGroup(textItem);

	QFont font = QFont("Arial", 18);
	textItem->setFont(font);
	
	setTextPos(size);

	backgroundItem->setBrush(background);
	textItem->setDefaultTextColor(textColor);
}

void Button::setText(const QString& text, const QColor& color) {
	textItem->setPlainText(text);
	textItem->setDefaultTextColor(color);
}

void Button::setBackground(const QBrush& background) {
	backgroundItem->setBrush(background);
}

void Button::setSize(const QPoint& size) {
	backgroundItem->setRect(0, 0, size.x(), size.y());
	setTextPos(size);
}

void Button::setTextPos(const QPoint& newSize) {
	int t_x = (newSize.x() / 2) - textItem->boundingRect().width() / 2;
	int t_y = (newSize.y() / 2) - textItem->boundingRect().height() / 2;
	textItem->setPos(t_x, t_y);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* eve) {
	emit btnClicked(eve);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* eve) {
	emit mouseEnter(eve);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* eve) {
	emit mouseLeave(eve);
}