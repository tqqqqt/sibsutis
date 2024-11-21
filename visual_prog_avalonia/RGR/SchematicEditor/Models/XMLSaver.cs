using SchematicEditor.Views;
using System;
using System.Collections.ObjectModel;
using System.Xml.Linq;

namespace SchematicEditor.Models
{
    public class XMLSaver : XMLSaverLoader
    {
        public void SaverHistory(ObservableCollection<ProjectHistory> tempColection, ProjectHistory newElement)
        {
            try
            {
                XDocument xDocument = new XDocument();
                XElement xElementColection = new XElement("historyColection");
                XElement xLastElement = new XElement("project");
                XAttribute xLastName = new XAttribute("name", newElement.Name);
                XElement xLastPAth = new XElement("path", newElement.Path);
                xLastElement.Add(xLastName);
                xLastElement.Add(xLastPAth);
                xElementColection.Add(xLastElement);
                for (int i = 0; i < tempColection.Count && i < 10; i++)
                {
                    if (tempColection[i] is ProjectHistory element)
                    {
                        if (element.Path != newElement.Path)
                        {
                            XElement xElement = new XElement("project");
                            XAttribute xElementName = new XAttribute("name", element.Name);
                            XElement xElementPAth = new XElement("path", element.Path);
                            xElement.Add(xElementName);
                            xElement.Add(xElementPAth);
                            xElementColection.Add(xElement);
                        }
                    }
                }
                xDocument.Add(xElementColection);
                xDocument.Save(historyPath);
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
                return;
            }
        }

        public void SaverHistroyNoNew(ObservableCollection<ProjectHistory> tempColection)
        {
            try
            {
                XDocument xDocument = new XDocument();
                XElement xElementColection = new XElement("historyColection");
                for (int i = 0; i < tempColection.Count && i < 10; i++)
                {
                    if (tempColection[i] is ProjectHistory element)
                    {
                        XElement xElement = new XElement("project");
                        XAttribute xElementName = new XAttribute("name", element.Name);
                        XElement xElementPAth = new XElement("path", element.Path);
                        xElement.Add(xElementName);
                        xElement.Add(xElementPAth);
                        xElementColection.Add(xElement);
                    }
                }
                xDocument.Add(xElementColection);
                xDocument.Save(historyPath);
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
                return;
            }
        }

        public void SaverProject(Project tempProject, string path)
        {
            try
            {
                XDocument xDocument = new XDocument();
                XElement xElementProject = new XElement("project");
                XAttribute xAttributeNameProject = new XAttribute("name", tempProject.Name);
                xElementProject.Add(xAttributeNameProject);
                foreach (Schema schema in tempProject.SchemaColection)
                {
                    XElement xElementColection = new XElement("schemaColection");
                    XAttribute xElementName = new XAttribute("name", schema.Name);
                    xElementColection.Add(xElementName);
                    foreach (ISchemaObject element in schema.ElementColection)
                    {
                        if (element is ElementIN elementIn)
                        {
                            XElement xElementIn = new XElement("elementIn");
                            XAttribute xAttributeInStatus = new XAttribute("status", elementIn.Status);
                            XElement xElementInOutSignal = new XElement("outSignal", elementIn.OutSignal);
                            XElement xElementInStartPoint = new XElement("startPoint", elementIn.StartPoint);
                            XElement xElementInIndex = new XElement("indexElement", elementIn.IndexElement);
                            xElementIn.Add(xAttributeInStatus);
                            xElementIn.Add(xElementInOutSignal);
                            xElementIn.Add(xElementInStartPoint);
                            xElementIn.Add(xElementInIndex);
                            xElementColection.Add(xElementIn);

                        }
                        else if (element is ElementOUT elementOut)
                        {
                            XElement xElementOut = new XElement("elementOut");
                            XAttribute xAttributeOutStatus = new XAttribute("status", elementOut.Status);
                            XElement xElementOutInSignal = new XElement("inSignal", elementOut.InSignal);
                            XElement xElementOutStartPoint = new XElement("startPoint", elementOut.StartPoint);
                            XElement xElementOutIndex = new XElement("indexElement", elementOut.IndexElement);
                            xElementOut.Add(xAttributeOutStatus);
                            xElementOut.Add(xElementOutInSignal);
                            xElementOut.Add(xElementOutStartPoint);
                            xElementOut.Add(xElementOutIndex);
                            xElementColection.Add(xElementOut);
                        }
                        else if (element is ElementAND elementAnd)
                        {
                            XElement xElementAnd = new XElement("elementAnd");
                            XElement xElementAndInSignal1 = new XElement("inSignal1", elementAnd.InSignal1);
                            XElement xElementAndInSignal2 = new XElement("inSignal2", elementAnd.InSignal2);
                            XElement xElementAndOutSignal = new XElement("outSignal", elementAnd.OutSignal);
                            XElement xElementAndStartPoint = new XElement("startPoint", elementAnd.StartPoint);
                            XElement xElementAndIndex = new XElement("indexElement", elementAnd.IndexElement);
                            xElementAnd.Add(xElementAndInSignal1);
                            xElementAnd.Add(xElementAndInSignal2);
                            xElementAnd.Add(xElementAndOutSignal);
                            xElementAnd.Add(xElementAndStartPoint);
                            xElementAnd.Add(xElementAndIndex);
                            xElementColection.Add(xElementAnd);
                        }
                        else if (element is ElementOR elementOr)
                        {
                            XElement xElementOr = new XElement("elementOr");
                            XElement xElementOrInSignal1 = new XElement("inSignal1", elementOr.InSignal1);
                            XElement xElementOrInSignal2 = new XElement("inSignal2", elementOr.InSignal2);
                            XElement xElementOrOutSignal = new XElement("outSignal", elementOr.OutSignal);
                            XElement xElementOrStartPoint = new XElement("startPoint", elementOr.StartPoint);
                            XElement xElementOrIndex = new XElement("indexElement", elementOr.IndexElement);
                            xElementOr.Add(xElementOrInSignal1);
                            xElementOr.Add(xElementOrInSignal2);
                            xElementOr.Add(xElementOrOutSignal);
                            xElementOr.Add(xElementOrStartPoint);
                            xElementOr.Add(xElementOrIndex);
                            xElementColection.Add(xElementOr);
                        }
                        else if (element is ElementNO elementNo)
                        {
                            XElement xElementNo = new XElement("elementNo");
                            XElement xElementNoInSignal = new XElement("inSignal", elementNo.InSignal);
                            XElement xElementNoOutSignal = new XElement("outSignal", elementNo.OutSignal);
                            XElement xElementNoStartPoint = new XElement("startPoint", elementNo.StartPoint);
                            XElement xElementNoIndex = new XElement("indexElement", elementNo.IndexElement);
                            xElementNo.Add(xElementNoInSignal);
                            xElementNo.Add(xElementNoOutSignal);
                            xElementNo.Add(xElementNoStartPoint);
                            xElementNo.Add(xElementNoIndex);
                            xElementColection.Add(xElementNo);
                        }
                        else if (element is ElementXOR elementXor)
                        {
                            XElement xElementXor = new XElement("elementXor");
                            XElement xElementXorInSignal1 = new XElement("inSignal1", elementXor.InSignal1);
                            XElement xElementXorInSignal2 = new XElement("inSignal2", elementXor.InSignal2);
                            XElement xElementXorOutSignal = new XElement("outSignal", elementXor.OutSignal);
                            XElement xElementXorStartPoint = new XElement("startPoint", elementXor.StartPoint);
                            XElement xElementXorIndex = new XElement("indexElement", elementXor.IndexElement);
                            xElementXor.Add(xElementXorInSignal1);
                            xElementXor.Add(xElementXorInSignal2);
                            xElementXor.Add(xElementXorOutSignal);
                            xElementXor.Add(xElementXorStartPoint);
                            xElementXor.Add(xElementXorIndex);
                            xElementColection.Add(xElementXor);
                        }
                        else if (element is ElementDE elementDe)
                        {
                            XElement xElementDe = new XElement("elementDe");
                            XElement xElementDeInSignal1 = new XElement("inSignal1", elementDe.InSignal1);
                            XElement xElementDeInSignal2 = new XElement("inSignal2", elementDe.InSignal2);
                            XElement xElementDeOutSignal1 = new XElement("outSignal1", elementDe.OutSignal);
                            XElement xElementDeOutSignal2 = new XElement("outSignal2", elementDe.OutSignal2);
                            XElement xElementDeStartPoint = new XElement("startPoint", elementDe.StartPoint);
                            XElement xElementDeIndex = new XElement("indexElement", elementDe.IndexElement);
                            xElementDe.Add(xElementDeInSignal1);
                            xElementDe.Add(xElementDeInSignal2);
                            xElementDe.Add(xElementDeOutSignal1);
                            xElementDe.Add(xElementDeOutSignal2);
                            xElementDe.Add(xElementDeStartPoint);
                            xElementDe.Add(xElementDeIndex);
                            xElementColection.Add(xElementDe);
                        }
                        else if (element is SchemaLine line)
                        {
                            XElement xElementLine = new XElement("line");
                            XElement xElementLineStartPoint = new XElement("startPoint", line.StartPoint);
                            XElement xELementLineEndPoint = new XElement("endPoint", line.EndPoint);
                            XElement xElementLineTypeFirstElement = new XElement("typeFirstElement", line.TypeFirstElement);
                            XElement xElementLineTypeSecondElement = new XElement("typeSecondElement", line.TypeSecondElement);
                            XElement xElementLineNameFirstElement = new XElement("nameFirstElement", line.NameFirstElement);
                            XElement xElementLineNameSecondElement = new XElement("nameSecondElement", line.NameSecondElement);
                            XElement xElementLineIndexFirstElement = new XElement("indexFirstElement", line.IndexFirstElement);
                            XElement xElementLineIndexSecondElement = new XElement("indexSecondElement", line.IndexSecondElement);
                            XElement xElementLineStatus = new XElement("status", line.Status);
                            xElementLine.Add(xElementLineStartPoint);
                            xElementLine.Add(xELementLineEndPoint);
                            xElementLine.Add(xElementLineTypeFirstElement);
                            xElementLine.Add(xElementLineTypeSecondElement);
                            xElementLine.Add(xElementLineNameFirstElement);
                            xElementLine.Add(xElementLineNameSecondElement);
                            xElementLine.Add(xElementLineIndexFirstElement);
                            xElementLine.Add(xElementLineIndexSecondElement);
                            xElementLine.Add(xElementLineStatus);
                            xElementColection.Add(xElementLine);
                        }
                    }
                    xElementProject.Add(xElementColection);
                }
                xDocument.Add(xElementProject);
                xDocument.Save(path);
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
                return;
            }
        }
    }
}
