using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Xml.Linq;

namespace Graphic.Models
{
    public class XmlFunction
    {
        public XmlFunction()
        { }

        public void XmlSave(string path, ObservableCollection<IFigure> figures_colection)
        {
            XDocument xDocument = new XDocument();
            XElement xElement_colection = new XElement("Figures");

            foreach (var element in figures_colection)
            {
                if (element is Gr_Line)
                {
                    Gr_Line line = (Gr_Line)element;
                    XElement xElementline = new XElement("Line");
                    XAttribute xAttributeName = new XAttribute("name", line.Name);
                    XElement xElementlineStroke = new XElement("stroke", line.StrokeColor);
                    XElement xElementlineStart = new XElement("start", line.StartPoint);
                    XElement xElementlineEnd = new XElement("end", line.EndPoint);
                    XElement xElementlineThic = new XElement("thic", line.StrokeThic);

                    xElementline.Add(xAttributeName);
                    xElementline.Add(xElementlineStroke);
                    xElementline.Add(xElementlineStart);
                    xElementline.Add(xElementlineEnd);
                    xElementline.Add(xElementlineThic);

                    xElement_colection.Add(xElementline);
                }
                else if (element is Gr_PolyLine)
                {
                    Gr_PolyLine poly = (Gr_PolyLine)element;
                    XElement xElementpoly = new XElement("PolyLine");
                    XAttribute xAttributeName = new XAttribute("name", poly.Name);
                    XElement xElementStroke = new XElement("stroke", poly.StrokeColor);
                    XElement xElementThic = new XElement("thic", poly.StrokeThic);
                    XElement xElementPoint = new XElement("points", poly.save_point);

                    xElementpoly.Add(xAttributeName);
                    xElementpoly.Add(xElementStroke);
                    xElementpoly.Add(xElementThic);
                    xElementpoly.Add(xElementPoint);

                    xElement_colection.Add(xElementpoly);
                }
                else if (element is Gr_Polygon)
                {
                    Gr_Polygon polygon = (Gr_Polygon)element;
                    XElement xPolygon = new XElement("Polygon");
                    XAttribute xName = new XAttribute("name", polygon.Name);
                    XElement xPoint = new XElement("points", polygon.save_point);
                    XElement xStroke = new XElement("stroke", polygon.StrokeColor);
                    XElement xThic = new XElement("thic", polygon.StrokeThic);
                    XElement xFill = new XElement("fill", polygon.Fill);

                    xPolygon.Add(xName);
                    xPolygon.Add(xPoint);
                    xPolygon.Add(xStroke);
                    xPolygon.Add(xThic);
                    xPolygon.Add(xFill);

                    xElement_colection.Add(xPolygon);
                }
                else if (element is Gr_Rectangle)
                {
                    Gr_Rectangle rec = (Gr_Rectangle)element;
                    XElement xRect = new("Rectangle");
                    XAttribute xName = new("name", rec.Name);
                    XElement xPoint = new("points", rec.Start_point);
                    XElement xWidth = new("width", rec.Width);
                    XElement xHeight = new("height", rec.Height);
                    XElement xThic = new("thic", rec.StrokeThic);
                    XElement xStroke = new("stroke", rec.StrokeColor);
                    XElement xFill = new("fill", rec.Fill);

                    xRect.Add(xName);
                    xRect.Add(xPoint);
                    xRect.Add(xWidth);
                    xRect.Add(xHeight);
                    xRect.Add(xThic);
                    xRect.Add(xStroke);
                    xRect.Add(xFill);

                    xElement_colection.Add(xRect);
                }
                else if (element is Gr_Ellipse)
                {
                    Gr_Ellipse el = (Gr_Ellipse)element;
                    XElement xElip = new("Ellipse");
                    XAttribute xName = new("name", el.Name);
                    XElement xPoint = new("points", el.StartPoint);
                    XElement xWidth = new("width", el.Width);
                    XElement xHeight = new("height", el.Height);
                    XElement xThic = new("thic", el.StrokeThic);
                    XElement xStroke = new("stroke", el.StrokeColor);
                    XElement xFill = new("fill", el.Fill);

                    xElip.Add(xName);
                    xElip.Add(xPoint);
                    xElip.Add(xWidth);
                    xElip.Add(xHeight);
                    xElip.Add(xThic);
                    xElip.Add(xStroke);
                    xElip.Add(xFill);

                    xElement_colection.Add(xElip);
                }
                else if (element is Gr_Path)
                {
                    Gr_Path pat = (Gr_Path)element;
                    XElement xPath = new("Path");
                    XAttribute xName = new("name", pat.Name);
                    XElement xThic = new("thic", pat.StrokeThic);
                    XElement xStroke = new("stoke", pat.StrokeColor);
                    XElement xPoint = new("command", pat.save_points);
                    XElement xFill = new("fill", pat.Fill);

                    xPath.Add(xName);
                    xPath.Add(xThic);
                    xPath.Add(xStroke);
                    xPath.Add(xPoint);
                    xPath.Add(xFill);

                    xElement_colection.Add(xPath);
                }
            }
            xDocument.Add(xElement_colection);
            xDocument.Save(path);
        }

        public IEnumerable<IFigure> XmlLoad(string path)
        {
            XDocument xDocument = XDocument.Load(path);
            System.Collections.Generic.IEnumerable<IFigure>? lines = xDocument.Element("Figures")?
                .Elements("Line")
                .Where(line =>
                {
                    var lName = line.Attribute("name");
                    var lStroke = line.Element("stroke");
                    var lStart = line.Element("start");
                    var lEnd = line.Element("end");
                    var lThic = line.Element("thic");
                    if (lName != null && lStroke != null && lStart != null && lEnd != null && lThic != null)
                    {
                        if (double.TryParse(lThic.Value, out double _) == true) return true;
                    }
                    return false;
                })
                .Select(line =>
                {
                    var lName = line.Attribute("name");
                    var lStroke = line.Element("stroke");
                    var lStart = line.Element("start");
                    var lEnd = line.Element("end");
                    var lThic = line.Element("thic");

                    return new Gr_Line(lName.Value, double.Parse(lThic.Value), lStroke.Value, lStart.Value, lEnd.Value);
                });
            IEnumerable<IFigure>? polys = xDocument.Element("Figures")?
                .Elements("PolyLine")
                .Where(poly =>
                    {
                        var pName = poly.Attribute("name");
                        var pStroke = poly.Element("stroke");
                        var pThic = poly.Element("thic");
                        var pPoint = poly.Element("points");
                        if (pName != null && pStroke != null && pThic != null && pPoint != null)
                        {
                            if (double.TryParse(pThic.Value, out double _) == true) return true;
                        }
                        return false;
                    })
                .Select(poly =>
                    {
                        var pName = poly.Attribute("name");
                        var pStroke = poly.Element("stroke");
                        var pThic = poly.Element("thic");
                        var pPoint = poly.Element("points");

                        return new Gr_PolyLine(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value));
                    });
            IEnumerable<IFigure>? polyg = xDocument.Element("Figures")?
                .Elements("Polygon")
                .Where(polyg =>
                {
                    var pName = polyg.Attribute("name");
                    var pPoint = polyg.Element("points");
                    var pStroke = polyg.Element("stroke");
                    var pThic = polyg.Element("thic");
                    var pFill = polyg.Element("fill");
                    if (pName != null && pPoint != null && pStroke != null && pThic != null && pFill != null)
                    {
                        if (double.TryParse(pThic.Value, out double _) == true) return true;
                    }
                    return false;
                })
                .Select(polyg =>
                {
                    var pName = polyg.Attribute("name");
                    var pPoint = polyg.Element("points");
                    var pStroke = polyg.Element("stroke");
                    var pThic = polyg.Element("thic");
                    var pFill = polyg.Element("fill");

                    return new Gr_Polygon(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value), pFill.Value);
                });
            IEnumerable<IFigure>? rect = xDocument.Element("Figures")?
                .Elements("Rectangle")
                .Where(rect =>
                {
                    var rName = rect.Attribute("name");
                    var rPoint = rect.Element("points");
                    var rWidth = rect.Element("width");
                    var rHeight = rect.Element("height");
                    var rThic = rect.Element("thic");
                    var rStroke = rect.Element("stroke");
                    var rFill = rect.Element("fill");
                    if (int.TryParse(rWidth.Value, out int _) == true && int.TryParse(rHeight.Value, out int _) == true && double.TryParse(rThic.Value, out double _) == true) return true;
                    return false;
                })
                .Select(rect =>
                {
                    var rName = rect.Attribute("name");
                    var rPoint = rect.Element("points");
                    var rWidth = rect.Element("width");
                    var rHeight = rect.Element("height");
                    var rThic = rect.Element("thic");
                    var rStroke = rect.Element("stroke");
                    var rFill = rect.Element("fill");

                    return new Gr_Rectangle(rName.Value, rPoint.Value, int.Parse(rWidth.Value), int.Parse(rHeight.Value), double.Parse(rThic.Value), rStroke.Value, rFill.Value);
                });
            IEnumerable<IFigure> elip = xDocument.Element("Figures")?
                .Elements("Ellipse")
                .Where(el =>
                {
                    var eName = el.Attribute("name");
                    var ePoint = el.Element("points");
                    var eWidth = el.Element("width");
                    var eHeight = el.Element("height");
                    var eThic = el.Element("thic");
                    var eStroke = el.Element("stroke");
                    var eFill = el.Element("fill");
                    if (int.TryParse(eHeight.Value, out int _) == true && int.TryParse(eWidth.Value, out int _) == true && double.TryParse(eThic.Value, out double _) == true) return true;
                    return false;
                })
                .Select(el =>
                {
                    var eName = el.Attribute("name");
                    var ePoint = el.Element("points");
                    var eWidth = el.Element("width");
                    var eHeight = el.Element("height");
                    var eThic = el.Element("thic");
                    var eStroke = el.Element("stroke");
                    var eFill = el.Element("fill");

                    return new Gr_Ellipse(eName.Value, int.Parse(eWidth.Value), int.Parse(eHeight.Value), ePoint.Value, eStroke.Value, double.Parse(eThic.Value), eFill.Value);
                });
            IEnumerable<IFigure> pat = xDocument.Element("Figures")?
                .Elements("Path")
                .Where(pa =>
                {
                    var pName = pa.Attribute("name");
                    var pThic = pa.Element("thic");
                    var pStroke = pa.Element("stoke");
                    var pPoint = pa.Element("command");
                    var pFill = pa.Element("fill");
                    if (double.TryParse(pThic.Value, out double _) == true) return true;
                    return false;
                })
                .Select(pa =>
                {
                    var pName = pa.Attribute("name");
                    var pThic = pa.Element("thic");
                    var pStroke = pa.Element("stoke");
                    var pPoint = pa.Element("command");
                    var pFill = pa.Element("fill");

                    return new Gr_Path(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value), pFill.Value);
                });


            var figures = lines.Concat(polys);
            figures = figures.Concat(polyg);
            figures = figures.Concat(rect);
            figures = figures.Concat(elip);
            figures = figures.Concat(pat);

            if (figures == null)
            {
                return new List<IFigure>();
            }

            return figures;
        }
    }

}
