import QtQuick
import QtQuick.Controls


//https://stackoverflow.com/questions/43406830/how-to-use-float-in-a-qml-spinbox
 
SpinBox{
    property int decimals: 3
    property real realValue: 0.0
    property real realFrom: 0.0
    property real realTo: 100.0
    property real realStepSize: 1.0
    property real factor: Math.pow(10, decimals)
    id: spinbox
    editable: true
    stepSize: realStepSize*factor
    value: realValue*factor
    to : realTo*factor
    from : realFrom*factor
    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)*spinbox.factor
        top:  Math.max(spinbox.from, spinbox.to)*spinbox.factor
    }
    textFromValue: function(value, locale) {
        return parseFloat(value*1.0/factor).toFixed(decimals);
    }
    //textToValue: function(text,locale) {
    //    var realValue = parseFloat(text)
    //    if (isNaN(realValue)){
    //        return spinbox.value
    //    }
    //    return realValue*factor
    //}
}
