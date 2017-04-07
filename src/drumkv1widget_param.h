// drumkv1widget_param.h
//
/****************************************************************************
   Copyright (C) 2012-2017, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __drumkv1widget_param_h
#define __drumkv1widget_param_h

#include <QWidget>
#include <QDial>
#include <QButtonGroup>


// Forward declarations.
class QLabel;
class QDoubleSpinBox;
class QComboBox;
class QCheckBox;


//-------------------------------------------------------------------------
// drumkv1widget_dial - A better QDial widget.

class drumkv1widget_dial : public QDial
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_dial(QWidget *pParent = 0);

	// Dial mode behavior:
	// DefaultMode - default (old) QDial behavior.
	// LinearMode  - proportionally to distance in one ortogonal axis.
	// AngularMode - angularly relative to widget center.
	enum DialMode { DefaultMode = 0, LinearMode, AngularMode };

	// Set knob dial mode behavior.
	static void setDialMode(DialMode dialMode);
	static DialMode dialMode();

protected:

	// Mouse angle determination.
	float mouseAngle(const QPoint& pos);

	// Alternate mouse behavior event handlers.
	void mousePressEvent(QMouseEvent *pMouseEvent);
	void mouseMoveEvent(QMouseEvent *pMouseEvent);
	void mouseReleaseEvent(QMouseEvent *pMouseEvent);

private:

	// Alternate mouse behavior tracking.
	bool   m_bMousePressed;
	QPoint m_posMouse;

	// Just for more precission on the movement
	float m_fLastDragValue;

	// Knob dial mode behavior.
	static DialMode g_dialMode;
};


//-------------------------------------------------------------------------
// drumkv1widget_param - Custom composite widget.

class drumkv1widget_param : public QWidget
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_param(QWidget *pParent = 0);

	// Accessors.
	virtual void setText(const QString& sText);
	virtual QString text() const;

	virtual void setMaximum(float fMaximum);
	float maximum() const;

	virtual void setMinimum(float fMinimum);
	float minimum() const;

	void resetDefaultValue();
	bool isDefaultValue() const;
	void setDefaultValue(float fDefaultValue);
	float defaultValue() const;

	virtual QString valueText() const;
	float value() const;

	// Scale multiplier accessors.
	void setScale(float fScale);
	float scale() const;

public slots:

	// Virtual accessor.
	virtual void setValue(float fValue, bool bDefault = false);

signals:

	// Change signal.
	void valueChanged(float);

protected:

	// Mouse behavior event handler.
	void mousePressEvent(QMouseEvent *pMouseEvent);

	// Scale/value converters.
	float scaleFromValue(float fValue) const;
	float valueFromScale(float fScale) const;

private:

	// Current value.
	float m_fValue;

	// Current value range.
	float m_fMinimum;
	float m_fMaximum;

	// Default value.
	float m_fDefaultValue;
	int   m_iDefaultValue;

	// Scale multiplier (default=100).
	float m_fScale;
};


//-------------------------------------------------------------------------
// drumkv1widget_knob - Custom knob/dial widget.

class drumkv1widget_knob : public drumkv1widget_param
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_knob(QWidget *pParent = 0);

	// Accessors.
	void setText(const QString& sText);
	QString text() const;

	void setMaximum(float fMaximum);
	void setMinimum(float fMinimum);

public slots:

	// Virtual accessor.
	void setValue(float fValue, bool bDefault = false);

protected slots:

	// Dial change slot.
	void dialValueChanged(int);

protected:

	// Scale-step accessors.
	void setSingleStep(float fSingleStep);
	float singleStep() const;

private:

	// Widget members.
	QLabel *m_pLabel;

	drumkv1widget_dial *m_pDial;
};


//-------------------------------------------------------------------------
// drumkv1widget_spin - Custom knob/spin-box widget.

class drumkv1widget_spin : public drumkv1widget_knob
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_spin(QWidget *pParent = 0);

	// Virtual accessors.
	void setMaximum(float fMaximum);
	void setMinimum(float fMinimum);

	QString valueText() const;

	// Specialized accessors.
	void setSpecialValueText(const QString& sText);
	QString specialValueText() const;

	bool isSpecialValue() const;

	void setDecimals(int iDecimals);
	int decimals() const;

public slots:

	// Virtual accessor.
	void setValue(float fValue, bool bDefault = false);

protected slots:

	// Change slot.
	void spinBoxValueChanged(double);

private:

	// Widget members.
	QDoubleSpinBox *m_pSpinBox;
};


//-------------------------------------------------------------------------
// drumkv1widget_combo - Custom knob/combo-box widget.

class drumkv1widget_combo : public drumkv1widget_knob
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_combo(QWidget *pParent = 0);

	// Virtual accessors.
	QString valueText() const;

	// Specialized accessors.
	void insertItems(int iIndex, const QStringList& items);
	void clear();

public slots:

	// Virtual accessor.
	void setValue(float fValue, bool bDefault = false);

protected slots:

	// Change slot.
	void comboBoxValueChanged(int);

protected:

	// Reimplemented mouse-wheel stepping.
	void wheelEvent(QWheelEvent *pWheelEvent);

private:

	// Widget members.
	QComboBox *m_pComboBox;
};


//-------------------------------------------------------------------------
// drumkv1widget_radio - Custom radio-button widget.

class drumkv1widget_radio : public drumkv1widget_param
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_radio(QWidget *pParent = 0);

	// Desstructor.
	~drumkv1widget_radio();

	// Virtual accessors.
	QString valueText() const;

	// Specialized accessors.
	void insertItems(int iIndex, const QStringList& items);
	void clear();

public slots:

	// Virtual accessor.
	void setValue(float fValue, bool bDefault = false);

protected slots:

	// Change slot.
	void radioGroupValueChanged(int);

private:

	// Widget members.
	QButtonGroup m_group;
};


//-------------------------------------------------------------------------
// drumkv1widget_check - Custom check-box widget.

class drumkv1widget_check : public drumkv1widget_param
{
	Q_OBJECT

public:

	// Constructor.
	drumkv1widget_check(QWidget *pParent = 0);

	// Desstructor.
	~drumkv1widget_check();

	// Accessors.
	void setText(const QString& sText);
	QString text() const;

	void setAlignment(Qt::Alignment alignment);
	Qt::Alignment alignment() const;

public slots:

	// Virtual accessor.
	void setValue(float fValue, bool bDefault = false);

protected slots:

	// Change slot.
	void checkBoxValueChanged(bool);

private:

	// Widget members.
	QCheckBox *m_pCheckBox;

	Qt::Alignment m_alignment;
};


#endif  // __drumkv1widget_param_h

// end of drumkv1widget_param.h
