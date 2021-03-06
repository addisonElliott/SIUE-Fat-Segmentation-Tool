#include "commands.h"
#include "axialslicewidget.h"
#include "coronalslicewidget.h"
#include "mainwindow.h"

// AxialMoveCommand
// --------------------------------------------------------------------------------------------------------------------
AxialMoveCommand::AxialMoveCommand(QPointF delta, AxialSliceWidget *widget, CommandID ID, QUndoCommand *parent) : QUndoCommand(parent),
    delta(delta), widget(widget), ID(ID)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Move axial image by (%1%, %2%)").arg(int(delta.x() * 100.0f)).arg(int(delta.y() * 100.0f)));
}

void AxialMoveCommand::undo()
{
    // Divide delta by respective width/height of screen and add it to the translation
    widget->rtranslation() -= delta;

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

void AxialMoveCommand::redo()
{
    // Add delta to translation
    widget->rtranslation() += delta;

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

bool AxialMoveCommand::mergeWith(const QUndoCommand *command)
{
    const AxialMoveCommand *moveCommand = static_cast<const AxialMoveCommand *>(command);

    // Merge the commands by adding their respective deltas
    delta += moveCommand->delta;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Move axial image by (%1%, %2%)").arg(int(delta.x()*100.0f)).arg(int(delta.y()*100.0f)));

    //if (delta.length() == 0)
    //    setObsolete(true);

    return true;
}

// CoronalMoveCommand
// --------------------------------------------------------------------------------------------------------------------
CoronalMoveCommand::CoronalMoveCommand(QPointF delta, CoronalSliceWidget *widget, CommandID ID, QUndoCommand *parent) : QUndoCommand(parent),
    delta(delta), widget(widget), ID(ID)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Move coronal image by (%1%, %2%)").arg(int(delta.x() * 100.0f)).arg(int(delta.y() * 100.0f)));
}

void CoronalMoveCommand::undo()
{
    // Divide delta by respective width/height of screen and add it to the translation
    widget->rtranslation() -= delta;

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

void CoronalMoveCommand::redo()
{
    // Add delta to translation
    widget->rtranslation() += delta;

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

bool CoronalMoveCommand::mergeWith(const QUndoCommand *command)
{
    const CoronalMoveCommand *moveCommand = static_cast<const CoronalMoveCommand *>(command);

    // Merge the commands by adding their respective deltas
    delta += moveCommand->delta;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Move coronal image by (%1%, %2%)").arg(int(delta.x()*100.0f)).arg(int(delta.y()*100.0f)));

    //if (delta.length() == 0)
    //    setObsolete(true);

    return true;
}

// AxialScaleCommand
// --------------------------------------------------------------------------------------------------------------------
AxialScaleCommand::AxialScaleCommand(float scaling, AxialSliceWidget *widget, QUndoCommand *parent) : QUndoCommand(parent),
    scaling(scaling), widget(widget)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Scale axial image by %1%").arg(int(scaling * 100.0f)));
}

void AxialScaleCommand::undo()
{
    // Add the scaling to the total scaling to zoom in or out
    widget->rscaling() -= scaling;

    // Clamp it between 0.05f (5%) to 3.0f (300%)
    widget->rscaling() = std::max(std::min(widget->rscaling(), 3.0f), 0.05f);

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

void AxialScaleCommand::redo()
{
    // Add the scaling to the total scaling to zoom in or out
    widget->rscaling() += scaling;

    // Clamp it between 0.05f (5%) to 3.0f (300%)
    widget->rscaling() = std::max(std::min(widget->rscaling(), 3.0f), 0.05f);

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

bool AxialScaleCommand::mergeWith(const QUndoCommand *command)
{
    const AxialScaleCommand *scaleCommand = static_cast<const AxialScaleCommand *>(command);

    // Merge the two commands by adding the scaling component
    scaling += scaleCommand->scaling;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Scale axial image by %1%").arg(int(scaling*100.0f)));

    // When building this executable, the setObsolete command requires a special patch in Qt to work
    // correctly. It is something that I edited in the Qt source code and contributed to the Qt source
    // code. It is likely that it will not become apart of the built libraries until Qt 5.9+. Therefore,
    // if you do not want to bother building the Qt libraries(6+ hours of time at least), then comment out
    // all instances of setObsolete and it should work. However, if you are interested, download the source
    // code and cherry-pick the patch at: https://codereview.qt-project.org/#/c/178852/
    //if (scaling == 0.0f)
    //    setObsolete(true);

    return true;
}

// CoronalScaleCommand
// --------------------------------------------------------------------------------------------------------------------
CoronalScaleCommand::CoronalScaleCommand(float scaling, CoronalSliceWidget *widget, QUndoCommand *parent) : QUndoCommand(parent),
    scaling(scaling), widget(widget)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Scale coronal image by %1%").arg(int(scaling * 100.0f)));
}

void CoronalScaleCommand::undo()
{
    // Add the scaling to the total scaling to zoom in or out
    widget->rscaling() -= scaling;

    // Clamp it between 0.05f (5%) to 3.0f (300%)
    widget->rscaling() = std::max(std::min(widget->rscaling(), 3.0f), 0.05f);

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

void CoronalScaleCommand::redo()
{
    // Add the scaling to the total scaling to zoom in or out
    widget->rscaling() += scaling;

    // Clamp it between 0.05f (5%) to 3.0f (300%)
    widget->rscaling() = std::max(std::min(widget->rscaling(), 3.0f), 0.05f);

    // Tell the screen to draw itself since the scene changed
    widget->update();
}

bool CoronalScaleCommand::mergeWith(const QUndoCommand *command)
{
    const CoronalScaleCommand *scaleCommand = static_cast<const CoronalScaleCommand *>(command);

    // Merge the two commands by adding the scaling component
    scaling += scaleCommand->scaling;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Scale coronal image by %1%").arg(int(scaling*100.0f)));

    // When building this executable, the setObsolete command requires a special patch in Qt to work
    // correctly. It is something that I edited in the Qt source code and contributed to the Qt source
    // code. It is likely that it will not become apart of the built libraries until Qt 5.9+. Therefore,
    // if you do not want to bother building the Qt libraries(6+ hours of time at least), then comment out
    // all instances of setObsolete and it should work. However, if you are interested, download the source
    // code and cherry-pick the patch at: https://codereview.qt-project.org/#/c/178852/
    //if (scaling == 0.0f)
    //    setObsolete(true);

    return true;
}

// ResetViewCommand
// --------------------------------------------------------------------------------------------------------------------
ResetViewCommand::ResetViewCommand(AxialSliceWidget *axialWidget, CoronalSliceWidget *coronalWidget, QUndoCommand *parent) : QUndoCommand(parent),
    oldAxialTranslate(axialWidget->rtranslation()), oldAxialScaling(axialWidget->rscaling()), oldCoronalTranslate(coronalWidget->rtranslation()),
    oldCoronalScaling(coronalWidget->rscaling()), axialWidget(axialWidget), coronalWidget(coronalWidget)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Reset view"));
}

void ResetViewCommand::undo()
{
    axialWidget->rtranslation() = oldAxialTranslate;
    axialWidget->rscaling() = oldAxialScaling;

    coronalWidget->rtranslation() = oldCoronalTranslate;
    coronalWidget->rscaling() = oldCoronalScaling;

    // Tell the screen to draw itself since the scene changed
    axialWidget->update();
    coronalWidget->update();
}

void ResetViewCommand::redo()
{
    // Reset the view for the axial and coronal widget
    axialWidget->resetView();
    coronalWidget->resetView();

    // Tell the screen to draw itself since the scene changed
    axialWidget->update();
    coronalWidget->update();
}

bool ResetViewCommand::mergeWith(const QUndoCommand *command)
{
    (void)command;

    // Do nothing

    return true;
}

// LocationChangeCommand
// --------------------------------------------------------------------------------------------------------------------
LocationChangeCommand::LocationChangeCommand(QVector4D newLocation, AxialSliceWidget *axialWidget, CoronalSliceWidget *coronalWidget,
                                             QSlider *axialSlider, QSpinBox *axialSpinBox, QSlider *coronalSlider, QSpinBox *coronalSpinBox,
                                             QSlider *saggitalSlider, QSpinBox *saggitalSpinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldLocation(axialWidget->getLocation()), newLocation(axialWidget->transformLocation(newLocation)), axialWidget(axialWidget), coronalWidget(coronalWidget),
    axialSlider(axialSlider), axialSpinBox(axialSpinBox), coronalSlider(coronalSlider), coronalSpinBox(coronalSpinBox),
    saggitalSlider(saggitalSlider), saggitalSpinBox(saggitalSpinBox)
{
    // Set text shown on QUndoView
    QVector4D delta = this->newLocation - oldLocation;
    QString str("Move to ");

    if (delta.x())
        str += QObject::tr("saggital slice %1, ").arg(newLocation.x());

    if (delta.y())
        str += QObject::tr("coronal slice %1, ").arg(newLocation.y());

    if (delta.z())
        str += QObject::tr("axial slice %1, ").arg(newLocation.z());

    if (delta.w())
        str += QObject::tr("time slice %1, ").arg(newLocation.w());

    str.remove(str.length() - 2, 2);
    setText(str);
}

void LocationChangeCommand::undo()
{
    // Go back to the old slice
    axialWidget->setLocation(oldLocation);
    coronalWidget->setLocation(oldLocation);

    QVector4D delta = newLocation - oldLocation;

    if (delta.z() && axialSlider && axialSpinBox)
    {
        // Set the slider value to be equal to the new slice. It blocks all signals from the setValue so that way
        // the valueChanged is not called again and creates a new LocationChangeCommand.
        bool prev = axialSlider->blockSignals(true);
        axialSlider->setValue(oldLocation.z());
        axialSlider->blockSignals(prev);

        // Set the spin box value to be equal to the new slice. It blocks all signals from the setValue so that way
        // the valueChanged is not called again and creates a new LocationChangeCommand.
        prev = axialSpinBox->blockSignals(true);
        axialSpinBox->setValue(oldLocation.z());
        axialSpinBox->blockSignals(prev);
    }

    if (delta.y() && coronalSlider && coronalSpinBox)
    {
        bool prev = coronalSlider->blockSignals(true);
        coronalSlider->setValue(oldLocation.y());
        coronalSlider->blockSignals(prev);

        prev = coronalSpinBox->blockSignals(true);
        coronalSpinBox->setValue(oldLocation.y());
        coronalSpinBox->blockSignals(prev);
    }

    if (delta.x() && saggitalSlider && saggitalSpinBox)
    {
        bool prev = saggitalSlider->blockSignals(true);
        saggitalSlider->setValue(oldLocation.x());
        saggitalSlider->blockSignals(prev);

        prev = saggitalSpinBox->blockSignals(true);
        saggitalSpinBox->setValue(oldLocation.x());
        saggitalSpinBox->blockSignals(prev);
    }
}

void LocationChangeCommand::redo()
{
    // Go to new location
    axialWidget->setLocation(newLocation);
    coronalWidget->setLocation(newLocation);

    QVector4D delta = newLocation - oldLocation;

    if (delta.z() && axialSlider && axialSpinBox)
    {
        // Set the slider value to be equal to the new slice. It blocks all signals from the setValue so that way
        // the valueChanged is not called again and creates a new LocationChangeCommand.
        bool prev = axialSlider->blockSignals(true);
        axialSlider->setValue(newLocation.z());
        axialSlider->blockSignals(prev);

        // Set the spin box value to be equal to the new slice. It blocks all signals from the setValue so that way
        // the valueChanged is not called again and creates a new LocationChangeCommand.
        prev = axialSpinBox->blockSignals(true);
        axialSpinBox->setValue(newLocation.z());
        axialSpinBox->blockSignals(prev);
    }

    if (delta.y() && coronalSlider && coronalSpinBox)
    {
        bool prev = coronalSlider->blockSignals(true);
        coronalSlider->setValue(newLocation.y());
        coronalSlider->blockSignals(prev);

        prev = coronalSpinBox->blockSignals(true);
        coronalSpinBox->setValue(newLocation.y());
        coronalSpinBox->blockSignals(prev);
    }

    if (delta.x() && saggitalSlider && saggitalSpinBox)
    {
        bool prev = saggitalSlider->blockSignals(true);
        saggitalSlider->setValue(newLocation.x());
        saggitalSlider->blockSignals(prev);

        prev = saggitalSpinBox->blockSignals(true);
        saggitalSpinBox->setValue(newLocation.x());
        saggitalSpinBox->blockSignals(prev);
    }

    //if (delta.isNull())
    //    setObsolete(true);
}

bool LocationChangeCommand::mergeWith(const QUndoCommand *command)
{
    const LocationChangeCommand *sliceChangeCommand = static_cast<const LocationChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldLocation of the current command (this) will stay
    // the same but the newLocation will change to what the merged command is
    newLocation = sliceChangeCommand->newLocation;

    // Update text shown on QUndoView
    QVector4D delta = newLocation - oldLocation;
    QString str("Move to ");

    if (delta.x())
        str.append(QObject::tr("saggital slice %1, ").arg(newLocation.x()));

    if (delta.y())
        str.append(QObject::tr("coronal slice %1, ").arg(newLocation.y()));

    if (delta.z())
        str.append(QObject::tr("axial slice %1, ").arg(newLocation.z()));

    if (delta.w())
        str.append(QObject::tr("time slice %1, ").arg(newLocation.w()));

    str.remove(str.length() - 2, 2);
    setText(str);

    //if (newLocation == oldLocation)
    //    setObsolete(true);

    return true;
}

// BrightnessChangeCommand
// --------------------------------------------------------------------------------------------------------------------
BrightnessChangeCommand::BrightnessChangeCommand(float newBrightness, AxialSliceWidget *widget, QSlider *slider, QSpinBox *spinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldBrightness(widget->getBrightness()), newBrightness(newBrightness), widget(widget), slider(slider), spinBox(spinBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Brightness set to %1%").arg(int(newBrightness * 100.0f)));
}

void BrightnessChangeCommand::undo()
{
    // Go back to the old brightness
    widget->setBrightness(oldBrightness);

    // Set the slider value to be equal to the old brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(oldBrightness * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the old brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(oldBrightness * 100.0f));
    spinBox->blockSignals(prev);
}

void BrightnessChangeCommand::redo()
{
    // Go to the new brightness
    widget->setBrightness(newBrightness);

    // Set the slider value to be equal to the new brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(newBrightness * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the new brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(newBrightness * 100.0f));
    spinBox->blockSignals(prev);
}

bool BrightnessChangeCommand::mergeWith(const QUndoCommand *command)
{
    const BrightnessChangeCommand *brightnessChangeCommand = static_cast<const BrightnessChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldBrightness of the current command (this) will stay
    // the same but the newBrightness will change to what the merged command is
    newBrightness = brightnessChangeCommand->newBrightness;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Brightness set to %1%").arg(int(newBrightness * 100.0f)));

    //if (newBrightness == oldBrightness)
    //   setObsolete(true);

    return true;
}

// BrightnessThresChangeCommand
// --------------------------------------------------------------------------------------------------------------------
BrightnessThresChangeCommand::BrightnessThresChangeCommand(float newThreshold, AxialSliceWidget *widget, QSpinBox *spinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldThreshold(widget->getBrightnessThreshold()), newThreshold(newThreshold), widget(widget), spinBox(spinBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Brightness threshold set to %1%").arg(int(newThreshold * 100.0f)));
}

void BrightnessThresChangeCommand::undo()
{
    // Go back to the old brightness threshold
    widget->setBrightnessThreshold(oldThreshold);

    // Set the spin box value to be equal to the old brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessThresChangeCommand.
    bool prev = spinBox->blockSignals(true);
    spinBox->setValue(int(oldThreshold * 100.0f));
    spinBox->blockSignals(prev);
}

void BrightnessThresChangeCommand::redo()
{
    // Go to the new brightness threshold
    widget->setBrightnessThreshold(newThreshold);

    // Set the spin box value to be equal to the new brightness. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new BrightnessThresChangeCommand.
    bool prev = spinBox->blockSignals(true);
    spinBox->setValue(int(newThreshold * 100.0f));
    spinBox->blockSignals(prev);
}

bool BrightnessThresChangeCommand::mergeWith(const QUndoCommand *command)
{
    const BrightnessThresChangeCommand *brightnessThresChangeCommand = static_cast<const BrightnessThresChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldBrightness of the current command (this) will stay
    // the same but the newBrightness will change to what the merged command is
    newThreshold = brightnessThresChangeCommand->newThreshold;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Brightness threshold set to %1%").arg(int(newThreshold * 100.0f)));

    //if (newThreshold == oldThreshold)
    //   setObsolete(true);

    return true;
}

// ContrastChangeCommand
// --------------------------------------------------------------------------------------------------------------------
ContrastChangeCommand::ContrastChangeCommand(float newContrast, AxialSliceWidget *widget, QSlider *slider, QSpinBox *spinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldContrast(widget->getContrast()), newContrast(newContrast), widget(widget), slider(slider), spinBox(spinBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Contrast set to %1%").arg(int(newContrast * 100.0f)));
}

void ContrastChangeCommand::undo()
{
    // Go back to the old contrast
    widget->setContrast(oldContrast);

    // Set the slider value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new ContrastChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(oldContrast * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new ContrastChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(oldContrast * 100.0f));
    spinBox->blockSignals(prev);
}

void ContrastChangeCommand::redo()
{
    // Go to the new brightness
    widget->setContrast(newContrast);

    // Set the slider value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new ContrastChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(newContrast * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new ContrastChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(newContrast * 100.0f));
    spinBox->blockSignals(prev);
}

bool ContrastChangeCommand::mergeWith(const QUndoCommand *command)
{
    const ContrastChangeCommand *contrastChangeCommand = static_cast<const ContrastChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldContrast of the current command (this) will stay
    // the same but the newContrast will change to what the merged command is
    newContrast = contrastChangeCommand->newContrast;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Contrast set to %1%").arg(int(newContrast * 100.0f)));

    //if (newContrast == oldContrast)
    //    setObsolete(true);

    return true;
}

// PrimColorMapChangeCommand
// --------------------------------------------------------------------------------------------------------------------
PrimColorMapChangeCommand::PrimColorMapChangeCommand(ColorMap newColor, AxialSliceWidget *widget, QComboBox *comboBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldColor(widget->getPrimColorMap()), newColor(newColor), widget(widget), comboBox(comboBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Primary color map set to %1").arg(comboBox->itemText((int)newColor)));
}

void PrimColorMapChangeCommand::undo()
{
    // Go back to the old color map
    widget->setPrimColorMap(oldColor);

    // Set the combo box value to be equal to the old color map. It blocks all signals from the setValue
    //so that way the valueChanged is not called again and creates a duplicate ColorMapChangeCommand.
    bool prev = comboBox->blockSignals(true);
    comboBox->setCurrentIndex((int)oldColor);
    comboBox->blockSignals(prev);
}

void PrimColorMapChangeCommand::redo()
{
    // Go to the new color map
    widget->setPrimColorMap(newColor);

    // Set the combo box value to be equal to the new color map. It blocks all signals from the setValue
    // so that way the valueChanged is not called again and creates a duplicate ColorMapChangeCommand.
    bool prev = comboBox->blockSignals(true);
    comboBox->setCurrentIndex((int)newColor);
    comboBox->blockSignals(prev);
}

// SecdColorMapChangeCommand
// --------------------------------------------------------------------------------------------------------------------
SecdColorMapChangeCommand::SecdColorMapChangeCommand(ColorMap newColor, AxialSliceWidget *widget, QComboBox *comboBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldColor(widget->getSecdColorMap()), newColor(newColor), widget(widget), comboBox(comboBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Secondary color map set to %1").arg(comboBox->itemText((int)newColor)));
}

void SecdColorMapChangeCommand::undo()
{
    // Go back to the old color map
    widget->setSecdColorMap(oldColor);

    // Set the combo box value to be equal to the old color map. It blocks all signals from the setValue
    //so that way the valueChanged is not called again and creates a duplicate ColorMapChangeCommand.
    bool prev = comboBox->blockSignals(true);
    comboBox->setCurrentIndex((int)oldColor);
    comboBox->blockSignals(prev);
}

void SecdColorMapChangeCommand::redo()
{
    // Go to the new color map
    widget->setSecdColorMap(newColor);

    // Set the combo box value to be equal to the new color map. It blocks all signals from the setValue
    // so that way the valueChanged is not called again and creates a duplicate ColorMapChangeCommand.
    bool prev = comboBox->blockSignals(true);
    comboBox->setCurrentIndex((int)newColor);
    comboBox->blockSignals(prev);
}

// PrimOpacityChangeCommand
// --------------------------------------------------------------------------------------------------------------------
PrimOpacityChangeCommand::PrimOpacityChangeCommand(float newOpacity, AxialSliceWidget *widget, QSlider *slider, QSpinBox *spinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldOpacity(widget->getPrimOpacity()), newOpacity(newOpacity), widget(widget), slider(slider), spinBox(spinBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Primary opacity set to %1%").arg(int(newOpacity * 100.0f)));
}

void PrimOpacityChangeCommand::undo()
{
    // Go back to the old opacity
    widget->setPrimOpacity(oldOpacity);

    // Set the slider value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new PrimOpacityChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(oldOpacity * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new PrimOpacityChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(oldOpacity * 100.0f));
    spinBox->blockSignals(prev);
}

void PrimOpacityChangeCommand::redo()
{
    // Go to the new brightness
    widget->setPrimOpacity(newOpacity);

    // Set the slider value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new PrimOpacityChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(newOpacity * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new PrimOpacityChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(newOpacity * 100.0f));
    spinBox->blockSignals(prev);
}

bool PrimOpacityChangeCommand::mergeWith(const QUndoCommand *command)
{
    const PrimOpacityChangeCommand *primOpacityChangeCommand = static_cast<const PrimOpacityChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldOpacity of the current command (this) will stay
    // the same but the newOpacity will change to what the merged command is
    newOpacity = primOpacityChangeCommand->newOpacity;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Primary opacity set to %1%").arg(int(newOpacity * 100.0f)));

    //if (newOpacity == oldOpacity)
    //    setObsolete(true);

    return true;
}

// SecdOpacityChangeCommand
// --------------------------------------------------------------------------------------------------------------------
SecdOpacityChangeCommand::SecdOpacityChangeCommand(float newOpacity, AxialSliceWidget *widget, QSlider *slider, QSpinBox *spinBox, QUndoCommand *parent) : QUndoCommand(parent),
    oldOpacity(widget->getSecdOpacity()), newOpacity(newOpacity), widget(widget), slider(slider), spinBox(spinBox)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Secondary opacity set to %1%").arg(int(newOpacity * 100.0f)));
}

void SecdOpacityChangeCommand::undo()
{
    // Go back to the old opacity
    widget->setSecdOpacity(oldOpacity);

    // Set the slider value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new SecdOpacityChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(oldOpacity * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the old contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new SecdOpacityChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(oldOpacity * 100.0f));
    spinBox->blockSignals(prev);
}

void SecdOpacityChangeCommand::redo()
{
    // Go to the new brightness
    widget->setSecdOpacity(newOpacity);

    // Set the slider value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new SecdOpacityChangeCommand.
    bool prev = slider->blockSignals(true);
    slider->setValue(int(newOpacity * 100.0f));
    slider->blockSignals(prev);

    // Set the spin box value to be equal to the new contrast. It blocks all signals from the setValue so that way
    // the valueChanged is not called again and creates a new SecdOpacityChangeCommand.
    prev = spinBox->blockSignals(true);
    spinBox->setValue(int(newOpacity * 100.0f));
    spinBox->blockSignals(prev);
}

bool SecdOpacityChangeCommand::mergeWith(const QUndoCommand *command)
{
    const SecdOpacityChangeCommand *secdOpacityChangeCommand = static_cast<const SecdOpacityChangeCommand *>(command);

    // Since the newest command will get merged with the older command, this means the oldOpacity of the current command (this) will stay
    // the same but the newOpacity will change to what the merged command is
    newOpacity = secdOpacityChangeCommand->newOpacity;

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Secondary opacity set to %1%").arg(int(newOpacity * 100.0f)));

    //if (newOpacity == oldOpacity)
    //    setObsolete(true);

    return true;
}

// SliceViewChangeCommand
// --------------------------------------------------------------------------------------------------------------------
SliceViewChangeCommand::SliceViewChangeCommand(SliceDisplayType newDT, AxialSliceWidget *widget, QRadioButton *oldBtn, QRadioButton *newBtn, QUndoCommand *parent) : QUndoCommand(parent),
    oldDT(widget->getDisplayType()), newDT(newDT), widget(widget), oldBtn(oldBtn), newBtn(newBtn)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Slice view set to %1").arg(newBtn->text()));
}

void SliceViewChangeCommand::undo()
{
    // Go back to the old slice view
    widget->setDisplayType(oldDT);

    // Check the old radio button which will automatically deselect the currently selected radio button
    // It blocks all signals from being called so that a duplicate SliceViewChangeCommand is not created
    bool prev = oldBtn->blockSignals(true);
    oldBtn->setChecked(true);
    oldBtn->blockSignals(prev);
}

void SliceViewChangeCommand::redo()
{
    // Go to the new slice view
    widget->setDisplayType(newDT);

    // Check the new radio button which will automatically deselect the currently selected radio button
    // It blocks all signals from being called so that a duplicate SliceViewChangeCommand is not created
    bool prev = newBtn->blockSignals(true);
    newBtn->setChecked(true);
    newBtn->blockSignals(prev);
}

// TracingLayerChangeCommand
// --------------------------------------------------------------------------------------------------------------------
TracingLayerChangeCommand::TracingLayerChangeCommand(TracingLayer newTracingLayer, AxialSliceWidget *widget, QRadioButton *oldBtn, QRadioButton *newBtn, QUndoCommand *parent) : QUndoCommand(parent),
    oldTracingLayer(widget->getTracingLayer()), newTracingLayer(newTracingLayer), widget(widget), oldBtn(oldBtn), newBtn(newBtn)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Tracing layer set to %1").arg(newBtn->text()));
}

void TracingLayerChangeCommand::undo()
{
    // Go back to the old tracing layer
    widget->setTracingLayer(oldTracingLayer);

    // Check the old radio button which will automatically deselect the currently selected radio button
    // It blocks all signals from being called so that a duplicate TracingLayerChangeCommand is not created
    bool prev = oldBtn->blockSignals(true);
    oldBtn->setChecked(true);
    oldBtn->blockSignals(prev);
}

void TracingLayerChangeCommand::redo()
{
    // Go to the new tracing layer
    widget->setTracingLayer(newTracingLayer);

    // Check the new radio button which will automatically deselect the currently selected radio button
    // It blocks all signals from being called so that a duplicate TracingLayerChangeCommand is not created
    bool prev = newBtn->blockSignals(true);
    newBtn->setChecked(true);
    newBtn->blockSignals(prev);
}

// TracingLayerVisibleChangeCommand
// --------------------------------------------------------------------------------------------------------------------
TracingLayerVisibleChangeCommand::TracingLayerVisibleChangeCommand(TracingLayer tracingLayer, bool newValue, AxialSliceWidget *widget, QCheckBox *btn, QUndoCommand *parent) : QUndoCommand(parent),
    tracingLayer(tracingLayer), newValue(newValue), widget(widget), btn(btn)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("%1 tracing layer %2").arg(newValue ? "Show" : "Hide").arg(btn->text()));
}

void TracingLayerVisibleChangeCommand::undo()
{
    // Set the tracing layer to the old visibility value
    widget->setTracingLayerVisible(tracingLayer, !newValue);

    // Check/Uncheck the checkbox based on old value (!newValue)
    // It blocks all signals from being called so that a duplicate TracingLayerChangeCommand is not created
    bool prev = btn->blockSignals(true);
    btn->setChecked(!newValue);
    btn->blockSignals(prev);

    widget->update();
}

void TracingLayerVisibleChangeCommand::redo()
{
    // Set the tracing layer to the new visibility value
    widget->setTracingLayerVisible(tracingLayer, newValue);

    // Check/Uncheck the checkbox based on new value (newValue)
    // It blocks all signals from being called so that a duplicate TracingLayerChangeCommand is not created
    bool prev = btn->blockSignals(true);
    btn->setChecked(newValue);
    btn->blockSignals(prev);

    widget->update();
}

// TracingPointsAddCommand
// --------------------------------------------------------------------------------------------------------------------
TracingPointsAddCommand::TracingPointsAddCommand(AxialSliceWidget *widget, QUndoCommand *parent) : TracingCommand(parent),
    widget(widget)
{
    // Get a text string based on the layer that points are being added too (current layer)
    QString str;
    switch (widget->getTracingLayer())
    {
        case TracingLayer::EAT: str = "EAT"; break;
        case TracingLayer::IMAT: str = "IMAT"; break;
        case TracingLayer::PAAT: str = "PAAT"; break;
        case TracingLayer::PAT: str = "PAT"; break;
        case TracingLayer::SCAT: str = "SCAT"; break;
        case TracingLayer::VAT: str = "VAT"; break;
    }

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Added points to %1 layer").arg(str));
}

void TracingPointsAddCommand::undo()
{
    const auto z = widget->getLocation().z();

    for (QPoint point : points)
        widget->getTraceSlices().reset(point.x(), point.y(), z);

    widget->setDirty(Dirty::Trace(widget->getTracingLayer()));
    widget->update();
}

void TracingPointsAddCommand::redo()
{
    const auto z = widget->getLocation().z();

    for (QPoint point : points)
        widget->getTraceSlices().set(point.x(), point.y(), z);

    widget->setDirty(Dirty::Trace(widget->getTracingLayer()));
    widget->update();
}

// TracingPointsEraseCommand
// --------------------------------------------------------------------------------------------------------------------
TracingPointsEraseCommand::TracingPointsEraseCommand(AxialSliceWidget *widget, QUndoCommand *parent) : TracingCommand(parent),
    widget(widget)
{
    // Get a text string based on the layer that points are being added too (current layer)
    QString str;
    switch (widget->getTracingLayer())
    {
        case TracingLayer::EAT: str = "EAT"; break;
        case TracingLayer::IMAT: str = "IMAT"; break;
        case TracingLayer::PAAT: str = "PAAT"; break;
        case TracingLayer::PAT: str = "PAT"; break;
        case TracingLayer::SCAT: str = "SCAT"; break;
        case TracingLayer::VAT: str = "VAT"; break;
    }

    // Updates text that is shown on QUndoView
    setText(QObject::tr("Erased points from %1 layer").arg(str));
}

void TracingPointsEraseCommand::undo()
{
    const auto z = widget->getLocation().z();

    for (QPoint point : points)
        widget->getTraceSlices().set(point.x(), point.y(), z);

    widget->setDirty(Dirty::Trace(widget->getTracingLayer()));
    widget->update();
}

void TracingPointsEraseCommand::redo()
{
    const auto z = widget->getLocation().z();

    for (QPoint point : points)
        widget->getTraceSlices().reset(point.x(), point.y(), z);

    widget->setDirty(Dirty::Trace(widget->getTracingLayer()));
    widget->update();
}

// DrawModeChangeCommand
// --------------------------------------------------------------------------------------------------------------------
DrawModeChangeCommand::DrawModeChangeCommand(DrawMode newDrawMode, AxialSliceWidget *widget, QStackedWidget *stackWidget, QPushButton *oldBtn, QPushButton *newBtn, QString str, QUndoCommand *parent) : QUndoCommand(parent),
    oldDrawMode(widget->getDrawMode()), newDrawMode(newDrawMode), widget(widget), stackWidget(stackWidget), oldBtn(oldBtn), newBtn(newBtn)
{
    // Updates text that is shown on QUndoView
    setText(QObject::tr("Draw mode set to %1").arg(str));
}

void DrawModeChangeCommand::undo()
{
    // Go back to the old drawing mode
    widget->setDrawMode(oldDrawMode);

    // Check the old button which will automatically deselect the currently selected button
    // It blocks all signals from being called so that a duplicate DrawModeChangeCommand is not created
    bool prev = oldBtn->blockSignals(true);
    oldBtn->setChecked(true);
    oldBtn->blockSignals(prev);

    stackWidget->setCurrentIndex((int)oldDrawMode);
}

void DrawModeChangeCommand::redo()
{
    // Go to the new drawing mode
    widget->setDrawMode(newDrawMode);

    // Check the new button which will automatically deselect the currently selected button
    // It blocks all signals from being called so that a duplicate DrawModeChangeCommand is not created
    bool prev = newBtn->blockSignals(true);
    newBtn->setChecked(true);
    newBtn->blockSignals(prev);

    stackWidget->setCurrentIndex((int)newDrawMode);
}
