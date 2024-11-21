using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Xml.Linq;

namespace ShemaPaint.Models
{
    public class XMLLoader : IColectionLoader
    {
        public IEnumerable<IFigures> Load(string path)
        {
            XDocument xDocument = XDocument.Load(path);
            XElement? colection = xDocument.Element("colection");
            if (colection is not null)
            {
                ObservableCollection<IFigures> loadColection = new ObservableCollection<IFigures>();
                foreach (XElement classElement in colection.Elements("class"))
                {
                    var className = classElement.Attribute("name");
                    var classSter = classElement.Element("ster");
                    var classVid = classElement.Element("vid");
                    var classStart = classElement.Element("start");
                    var classFont = classElement.Element("mainFont");
                    var classWidth = classElement.Element("width");
                    var classHeight = classElement.Element("height");
                    ObservableCollection<Atrib> atribColection = new ObservableCollection<Atrib>();
                    foreach (XElement atribElement in classElement.Elements("atribElement"))
                    {
                        var atribName = atribElement.Attribute("name");
                        var atribType = atribElement.Element("type");
                        var atribVid = atribElement.Element("vid");
                        var atribSter = atribElement.Element("ster");
                        var atribValue = atribElement.Element("value");
                        Atrib atribElementColection = new Atrib
                        {
                            Name = atribName.Value,
                            Type = atribType.Value,
                            Vidim = atribVid.Value,
                            Stereot = atribSter.Value,
                            AtribValue = atribValue.Value,
                        };
                        atribColection.Add(atribElementColection);
                    }
                    ObservableCollection<Oper> operColection = new ObservableCollection<Oper>();
                    foreach (XElement operElement in classElement.Elements("operElement"))
                    {
                        var operName = operElement.Attribute("name");
                        var operType = operElement.Element("type");
                        var operVid = operElement.Element("vid");
                        var operSter = operElement.Element("ster");
                        var operParName = operElement.Element("parName");
                        var operParType = operElement.Element("parType");
                        Oper operElementColection = new Oper
                        {
                            OpName = operName.Value,
                            OpType = operType.Value,
                            OpVidim = operVid.Value,
                            OpSter = operSter.Value,
                            ParName = operParName.Value,
                            ParType = operParType.Value,
                        };
                        operColection.Add(operElementColection);
                    }
                    El_Class classElementColection = new El_Class
                    {
                        Name = className.Value,
                        Stereotip = classSter.Value,
                        Vidimost = classVid.Value,
                        StartPoint = Avalonia.Point.Parse(classStart.Value),
                        FontSizeMain = double.Parse(classFont.Value),
                        Width = double.Parse(classWidth.Value),
                        Height = double.Parse(classHeight.Value),
                    };
                    classElementColection.Atrib_colection = atribColection;
                    classElementColection.Oper_colection = operColection;
                    loadColection.Add(classElementColection);
                }
                foreach (XElement interfaceElement in colection.Elements("interface"))
                {
                    var interfaceName = interfaceElement.Attribute("name");
                    var interfaceSter = interfaceElement.Element("ster");
                    var interfaceVid = interfaceElement.Element("vid");
                    var interfaceStart = interfaceElement.Element("start");
                    var interfaceFont = interfaceElement.Element("mainFont");
                    var interfaceWidth = interfaceElement.Element("width");
                    var interfaceHeight = interfaceElement.Element("height");
                    ObservableCollection<Atrib> atribColection = new ObservableCollection<Atrib>();
                    foreach (XElement atribElement in interfaceElement.Elements("atribElement"))
                    {
                        var atribName = atribElement.Attribute("name");
                        var atribType = atribElement.Element("type");
                        var atribVid = atribElement.Element("vid");
                        var atribSter = atribElement.Element("ster");
                        var atribValue = atribElement.Element("value");
                        Atrib atribElementColection = new Atrib
                        {
                            Name = atribName.Value,
                            Type = atribType.Value,
                            Vidim = atribVid.Value,
                            Stereot = atribSter.Value,
                            AtribValue = atribValue.Value,
                        };
                        atribColection.Add(atribElementColection);
                    }
                    ObservableCollection<Oper> operColection = new ObservableCollection<Oper>();
                    foreach (XElement operElement in interfaceElement.Elements("operElement"))
                    {
                        var operName = operElement.Attribute("name");
                        var operType = operElement.Element("type");
                        var operVid = operElement.Element("vid");
                        var operSter = operElement.Element("ster");
                        var operParName = operElement.Element("parName");
                        var operParType = operElement.Element("parType");
                        Oper operElementColection = new Oper
                        {
                            OpName = operName.Value,
                            OpType = operType.Value,
                            OpVidim = operVid.Value,
                            OpSter = operSter.Value,
                            ParName = operParName.Value,
                            ParType = operParType.Value,
                        };
                        operColection.Add(operElementColection);
                    }
                    El_Interface interfaceElementColection = new El_Interface
                    {
                        Name = interfaceName.Value,
                        Stereotip = interfaceSter.Value,
                        Vidimost = interfaceVid.Value,
                        StartPoint = Avalonia.Point.Parse(interfaceStart.Value),
                        FontSizeMain = double.Parse(interfaceFont.Value),
                        Width = double.Parse(interfaceWidth.Value),
                        Height = double.Parse(interfaceHeight.Value),
                    };
                    interfaceElementColection.AtribColection = atribColection;
                    interfaceElementColection.OperColection = operColection;
                    loadColection.Add(interfaceElementColection);
                }
                foreach (XElement lineElement in colection.Elements("line"))
                {
                    var lineType = lineElement.Attribute("type");
                    var lineStart = lineElement.Element("start");
                    var lineEnd = lineElement.Element("end");
                    var className1 = lineElement.Element("firstClass");
                    var className2 = lineElement.Element("secondClass");
                    var interfaceName1 = lineElement.Element("firstInterface");
                    var interfaceName2 = lineElement.Element("secondInterface");
                    ILines? lineElementColection = null;
                    if (lineType.Value == "Nasled")
                    {
                        lineElementColection = new LineNasled
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    else if (lineType.Value == "Realiz")
                    {
                        lineElementColection = new LineRealiz
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    else if (lineType.Value == "Zavis")
                    {
                        lineElementColection = new LineZavis
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    else if (lineType.Value == "Agreg")
                    {
                        lineElementColection = new LineAgreg
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    else if (lineType.Value == "Compos")
                    {
                        lineElementColection = new LineCompos
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    else if (lineType.Value == "Acos")
                    {
                        lineElementColection = new LineAsoc
                        {
                            StartPoint = Avalonia.Point.Parse(lineStart.Value),
                            EndPoint = Avalonia.Point.Parse(lineEnd.Value),
                        };
                    }
                    if (lineElementColection != null)
                    {
                        if (className1 != null) lineElementColection.NameFirstClass = className1.Value;
                        if (className2 != null) lineElementColection.NameSecondClass = className2.Value;
                        if (interfaceName1 != null) lineElementColection.NameFirstInterface = interfaceName1.Value;
                        if (interfaceName2 != null) lineElementColection.NameSecondInterface = interfaceName2.Value;
                        lineElementColection.PathUpdate();
                        loadColection.Add(lineElementColection);
                    }
                }
                if (loadColection != null)
                {
                    return loadColection;
                }
                else return new List<IFigures>();
            }
            return new List<IFigures>();
        }
    }
}
