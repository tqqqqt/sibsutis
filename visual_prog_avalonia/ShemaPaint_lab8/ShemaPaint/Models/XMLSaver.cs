using System.Collections.Generic;
using System.Xml.Linq;

namespace ShemaPaint.Models
{
    public class XMLSaver : IColectionSaver
    {
        public void Save(IEnumerable<IFigures> colection, string path)
        {
            XDocument xDocument = new XDocument();
            XElement xElementColection = new XElement("colection");
            foreach (IFigures element in colection)
            {
                if (element is El_Class elClass)
                {
                    XElement xElementClass = new XElement("class");
                    XAttribute xAttributClassName = new XAttribute("name", elClass.Name);
                    XElement xElementStereotip = new XElement("ster", elClass.Stereotip);
                    XElement xElementVidimost = new XElement("vid", elClass.Vidimost);
                    XElement xElementStart = new XElement("start", elClass.StartPoint);
                    XElement xElementMain = new XElement("mainFont", elClass.FontSizeMain);
                    XElement xElementWidth = new XElement("width", elClass.Width);
                    XElement xElementHeight = new XElement("height", elClass.Height);
                    xElementClass.Add(xAttributClassName);
                    xElementClass.Add(xElementStereotip);
                    xElementClass.Add(xElementVidimost);
                    xElementClass.Add(xElementStart);
                    xElementClass.Add(xElementMain);
                    xElementClass.Add(xElementWidth);
                    xElementClass.Add(xElementHeight);
                    foreach (Atrib atrib in elClass.Atrib_colection)
                    {
                        XElement xElementAtribElement = new XElement("atribElement");
                        XAttribute xAttribAtribName = new XAttribute("name", atrib.Name);
                        XElement xElementAtribType = new XElement("type", atrib.Type);
                        XElement xElementAtribVid = new XElement("vid", atrib.Vidim);
                        XElement xElementAtribSter = new XElement("ster", atrib.Stereot);
                        XElement xElementAtribValue = new XElement("value", atrib.AtribValue);
                        xElementAtribElement.Add(xAttribAtribName);
                        xElementAtribElement.Add(xElementAtribType);
                        xElementAtribElement.Add(xElementAtribVid);
                        xElementAtribElement.Add(xElementAtribSter);
                        xElementAtribElement.Add(xElementAtribValue);
                        xElementClass.Add(xElementAtribElement);
                    }
                    foreach (Oper oper in elClass.Oper_colection)
                    {
                        XElement xElementOperElement = new XElement("operElement");
                        XAttribute xAttributeOperName = new XAttribute("name", oper.OpName);
                        XElement xElementOperType = new XElement("type", oper.OpType);
                        XElement xElementOperVid = new XElement("vid", oper.OpVidim);
                        XElement xElementOperSter = new XElement("ster", oper.OpSter);
                        XElement xElementOperParName = new XElement("parName", oper.ParName);
                        XElement xElementOperParType = new XElement("parType", oper.ParType);
                        xElementOperElement.Add(xAttributeOperName);
                        xElementOperElement.Add(xElementOperType);
                        xElementOperElement.Add(xElementOperVid);
                        xElementOperElement.Add(xElementOperSter);
                        xElementOperElement.Add(xElementOperParName);
                        xElementOperElement.Add(xElementOperParType);
                        xElementClass.Add(xElementOperElement);
                    }
                    xElementColection.Add(xElementClass);
                }
                else if (element is El_Interface elInterface)
                {
                    XElement xElementInterface = new XElement("interface");
                    XAttribute xAttributInterName = new XAttribute("name", elInterface.Name);
                    XElement xElementStereotip = new XElement("ster", elInterface.Stereotip);
                    XElement xElementVidimost = new XElement("vid", elInterface.Vidimost);
                    XElement xElementStart = new XElement("start", elInterface.StartPoint);
                    XElement xElementFont = new XElement("mainFont", elInterface.FontSizeMain);
                    XElement xElementWidth = new XElement("width", elInterface.Width);
                    XElement xElementHeight = new XElement("height", elInterface.Height);
                    xElementInterface.Add(xAttributInterName);
                    xElementInterface.Add(xElementStereotip);
                    xElementInterface.Add(xElementVidimost);
                    xElementInterface.Add(xElementStart);
                    xElementInterface.Add(xElementFont);
                    xElementInterface.Add(xElementWidth);
                    xElementInterface.Add(xElementHeight);
                    foreach (Atrib atrib in elInterface.AtribColection)
                    {
                        XElement xElementAtribElement = new XElement("atribElement");
                        XAttribute xAttribAtribName = new XAttribute("name", atrib.Name);
                        XElement xElementAtribType = new XElement("type", atrib.Type);
                        XElement xElementAtribVid = new XElement("vid", atrib.Vidim);
                        XElement xElementAtribSter = new XElement("ster", atrib.Stereot);
                        XElement xElementAtribValue = new XElement("value", atrib.AtribValue);
                        xElementAtribElement.Add(xAttribAtribName);
                        xElementAtribElement.Add(xElementAtribType);
                        xElementAtribElement.Add(xElementAtribVid);
                        xElementAtribElement.Add(xElementAtribSter);
                        xElementAtribElement.Add(xElementAtribValue);
                        xElementInterface.Add(xElementAtribElement);
                    }
                    foreach (Oper oper in elInterface.OperColection)
                    {
                        XElement xElementOperElement = new XElement("operElement");
                        XAttribute xAttributeOperName = new XAttribute("name", oper.OpName);
                        XElement xElementOperType = new XElement("type", oper.OpType);
                        XElement xElementOperVid = new XElement("vid", oper.OpVidim);
                        XElement xElementOperSter = new XElement("ster", oper.OpSter);
                        XElement xElementOperParName = new XElement("parName", oper.ParName);
                        XElement xElementOperParType = new XElement("parType", oper.ParType);
                        xElementOperElement.Add(xAttributeOperName);
                        xElementOperElement.Add(xElementOperType);
                        xElementOperElement.Add(xElementOperVid);
                        xElementOperElement.Add(xElementOperSter);
                        xElementOperElement.Add(xElementOperParName);
                        xElementOperElement.Add(xElementOperParType);
                        xElementInterface.Add(xElementOperElement);
                    }
                    xElementColection.Add(xElementInterface);
                }
                else if (element is ILines elLines)
                {
                    XElement xElementLine = new XElement("line");
                    XAttribute xAttributeType = new XAttribute("type", elLines.LineType);
                    XElement xElementStart = new XElement("start", elLines.StartPoint);
                    XElement xElementEnd = new XElement("end", elLines.EndPoint);
                    XElement xElementClass1 = new XElement("firstClass", elLines.NameFirstClass);
                    XElement xElementClass2 = new XElement("secondClass", elLines.NameSecondClass);
                    XElement xElementInterface1 = new XElement("firstInterface", elLines.NameFirstInterface);
                    XElement xElementInterface2 = new XElement("secondInterface", elLines.NameSecondInterface);
                    xElementLine.Add(xAttributeType);
                    xElementLine.Add(xElementStart);
                    xElementLine.Add(xElementEnd);
                    xElementLine.Add(xElementClass1);
                    xElementLine.Add(xElementClass2);
                    xElementLine.Add(xElementInterface1);
                    xElementLine.Add(xElementInterface2);
                    xElementColection.Add(xElementLine);
                }
            }
            xDocument.Add(xElementColection);
            xDocument.Save(path);
        }
    }
}
