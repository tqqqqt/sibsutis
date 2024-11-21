using SchematicEditor.Views;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Xml.Linq;

namespace SchematicEditor.Models
{
    public class XMLLoader : XMLSaverLoader
    {
        public IEnumerable<ProjectHistory> LoadHistory()
        {
            try
            {
                XDocument xDocument = XDocument.Load(historyPath);
                XElement? xColection = xDocument.Element("historyColection");
                if (xColection is not null)
                {
                    ObservableCollection<ProjectHistory> historyColection = new ObservableCollection<ProjectHistory>();
                    foreach (XElement projectElement in xColection.Elements("project"))
                    {
                        var projectName = projectElement.Attribute("name");
                        var projectPath = projectElement.Element("path");
                        ProjectHistory projectHistory = new ProjectHistory
                        {
                            Name = projectName.Value,
                            Path = projectPath.Value,
                        };
                        historyColection.Add(projectHistory);
                    }
                    if (historyColection != null)
                    {
                        return historyColection;
                    }
                    else return new List<ProjectHistory>();
                }
                else return new List<ProjectHistory>();
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
                return new List<ProjectHistory>();
            }
        }

        public Project LoadProject(string path)
        {
            try
            {
                XDocument xDocument = XDocument.Load(path);
                XElement? xProject = xDocument.Element("project");
                if (xProject != null)
                {
                    var projectName = xProject.Attribute("name");
                    ObservableCollection<Schema> loadColectionSchema = new ObservableCollection<Schema>();
                    foreach (XElement xElementSchema in xProject.Elements("schemaColection"))
                    {
                        var schemaName = xElementSchema.Attribute("name");
                        ObservableCollection<ISchemaObject> loadElementColection = new ObservableCollection<ISchemaObject>();
                        foreach (XElement xElementIn in xElementSchema.Elements("elementIn"))
                        {
                            var inStatus = xElementIn.Attribute("status");
                            var inOutSignal = xElementIn.Element("outSignal");
                            var inStartPoint = xElementIn.Element("startPoint");
                            var inIndex = xElementIn.Element("indexElement");
                            ElementIN elementIn = new ElementIN
                            {
                                Status = int.Parse(inStatus.Value),
                                OutSignal = int.Parse(inOutSignal.Value),
                                StartPoint = Avalonia.Point.Parse(inStartPoint.Value),
                                IndexElement = int.Parse(inIndex.Value),
                            };
                            loadElementColection.Add(elementIn);
                        }
                        foreach (XElement xElementOut in xElementSchema.Elements("elementOut"))
                        {
                            var outStatus = xElementOut.Attribute("status");
                            var outInSignal = xElementOut.Element("inSignal");
                            var outStartPoint = xElementOut.Element("startPoint");
                            var outIndex = xElementOut.Element("indexElement");
                            ElementOUT elementOut = new ElementOUT
                            {
                                Status = int.Parse(outStatus.Value),
                                InSignal = int.Parse(outInSignal.Value),
                                StartPoint = Avalonia.Point.Parse(outStartPoint.Value),
                                IndexElement = int.Parse(outIndex.Value),
                            };
                            loadElementColection.Add(elementOut);
                        }
                        foreach (XElement xElementAnd in xElementSchema.Elements("elementAnd"))
                        {
                            var andInSignal1 = xElementAnd.Element("inSignal1");
                            var andInSignal2 = xElementAnd.Element("inSignal2");
                            var andOutSignal = xElementAnd.Element("outSignal");
                            var andStartPoint = xElementAnd.Element("startPoint");
                            var andIndex = xElementAnd.Element("indexElement");
                            ElementAND elementAnd = new ElementAND
                            {
                                InSignal1 = int.Parse(andInSignal1.Value),
                                InSignal2 = int.Parse(andInSignal2.Value),
                                OutSignal = int.Parse(andOutSignal.Value),
                                StartPoint = Avalonia.Point.Parse(andStartPoint.Value),
                                IndexElement = int.Parse(andIndex.Value),
                            };
                            loadElementColection.Add(elementAnd);
                        }
                        foreach (XElement xElementOr in xElementSchema.Elements("elementOr"))
                        {
                            var orInSignal1 = xElementOr.Element("inSignal1");
                            var orInSignal2 = xElementOr.Element("inSignal2");
                            var orOutSignal = xElementOr.Element("outSignal");
                            var orStartPoint = xElementOr.Element("startPoint");
                            var orIndex = xElementOr.Element("indexElement");
                            ElementOR elementOr = new ElementOR
                            {
                                InSignal1 = int.Parse(orInSignal1.Value),
                                InSignal2 = int.Parse(orInSignal2.Value),
                                OutSignal = int.Parse(orOutSignal.Value),
                                StartPoint = Avalonia.Point.Parse(orStartPoint.Value),
                                IndexElement = int.Parse(orIndex.Value),
                            };
                            loadElementColection.Add(elementOr);
                        }
                        foreach (XElement xElementNo in xElementSchema.Elements("elementNo"))
                        {
                            var noInSignal = xElementNo.Element("inSignal");
                            var noOutSignal = xElementNo.Element("outSignal");
                            var noStartPoint = xElementNo.Element("startPoint");
                            var noIndex = xElementNo.Element("indexElement");
                            ElementNO elementNo = new ElementNO
                            {
                                InSignal = int.Parse(noInSignal.Value),
                                OutSignal = int.Parse(noOutSignal.Value),
                                StartPoint = Avalonia.Point.Parse(noStartPoint.Value),
                                IndexElement = int.Parse(noIndex.Value),
                            };
                            loadElementColection.Add(elementNo);
                        }
                        foreach (XElement xElementXor in xElementSchema.Elements("elementXor"))
                        {
                            var xorInSignal1 = xElementXor.Element("inSignal1");
                            var xorInSignal2 = xElementXor.Element("inSignal2");
                            var xorOutSignal = xElementXor.Element("outSignal");
                            var xorStartPoint = xElementXor.Element("startPoint");
                            var xorIndex = xElementXor.Element("indexElement");
                            ElementXOR elementXor = new ElementXOR
                            {
                                InSignal1 = int.Parse(xorInSignal1.Value),
                                InSignal2 = int.Parse(xorInSignal2.Value),
                                OutSignal = int.Parse(xorOutSignal.Value),
                                StartPoint = Avalonia.Point.Parse(xorStartPoint.Value),
                                IndexElement = int.Parse(xorIndex.Value),
                            };
                            loadElementColection.Add(elementXor);
                        }
                        foreach (XElement xElementDe in xElementSchema.Elements("elementDe"))
                        {
                            var deInSignal1 = xElementDe.Element("inSignal1");
                            var deInSignal2 = xElementDe.Element("inSignal2");
                            var deOutSignal1 = xElementDe.Element("outSignal1");
                            var deOutSignal2 = xElementDe.Element("outSignal2");
                            var deStartPoint = xElementDe.Element("startPoint");
                            var deIndex = xElementDe.Element("indexElement");
                            ElementDE elementDe = new ElementDE
                            {
                                InSignal1 = int.Parse(deInSignal1.Value),
                                InSignal2 = int.Parse(deInSignal2.Value),
                                OutSignal = int.Parse(deOutSignal1.Value),
                                OutSignal2 = int.Parse(deOutSignal2.Value),
                                StartPoint = Avalonia.Point.Parse(deStartPoint.Value),
                                IndexElement = int.Parse(deIndex.Value),
                            };
                            loadElementColection.Add(elementDe);
                        }
                        foreach (XElement xElementLine in xElementSchema.Elements("line"))
                        {
                            var lineStartPoint = xElementLine.Element("startPoint");
                            var lineEndPoint = xElementLine.Element("endPoint");
                            var lineTypeFirst = xElementLine.Element("typeFirstElement");
                            var lineTypeSecond = xElementLine.Element("typeSecondElement");
                            var lineNameFirst = xElementLine.Element("nameFirstElement");
                            var lineNameSecond = xElementLine.Element("nameSecondElement");
                            var indexFirstElement = xElementLine.Element("indexFirstElement");
                            var indexSecondElement = xElementLine.Element("indexSecondElement");
                            var lineStatus = xElementLine.Element("status");
                            SchemaLine line = new SchemaLine
                            {
                                StartPoint = Avalonia.Point.Parse(lineStartPoint.Value),
                                EndPoint = Avalonia.Point.Parse(lineEndPoint.Value),
                                TypeFirstElement = int.Parse(lineTypeFirst.Value),
                                TypeSecondElement = int.Parse(lineTypeSecond.Value),
                                NameFirstElement = lineNameFirst.Value,
                                NameSecondElement = lineNameSecond.Value,
                                IndexFirstElement = int.Parse(indexFirstElement.Value),
                                IndexSecondElement = int.Parse(indexSecondElement.Value),
                                Status = int.Parse(lineStatus.Value),
                            };
                            loadElementColection.Add(line);
                        }
                        Schema loadSchema = new Schema
                        {
                            Name = schemaName.Value,
                            ElementColection = loadElementColection,
                        };
                        loadColectionSchema.Add(loadSchema);
                    }
                    Project loadProject = new Project
                    {
                        Name = projectName.Value,
                        SchemaColection = loadColectionSchema,
                    };
                    if (loadProject != null)
                    {
                        return loadProject;
                    }
                    else return new Project
                    {
                        Name = "project",
                    };
                }
                else return new Project
                {
                    Name = "project",
                };
            }
            catch (Exception error)
            {
                var errorWindow = new ErrorWindow(error.Message);
                errorWindow.Show();
                return new Project
                {
                    Name = "project"
                };
            }
        }
    }
}
