using Avalonia.Controls.Shapes;
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
                    XElement xElementART = new XElement("angleRT", line.AngleRT);
                    XElement xElementRTX = new XElement("rtx", line.RTX);
                    XElement xElementRTY = new XElement("rty", line.RTY);
                    XElement xElementSTX = new XElement("stx", line.STX);
                    XElement xElementSTY = new XElement("sty", line.STY);
                    XElement xElementASTX = new XElement("astx", line.AngleSTX);
                    XElement xElementASTY = new XElement("asty", line.AngleSTY);
                    XElement xElementPos = new XElement("pos", line.Pos);

                    xElementline.Add(xAttributeName);
                    xElementline.Add(xElementlineStroke);
                    xElementline.Add(xElementlineStart);
                    xElementline.Add(xElementlineEnd);
                    xElementline.Add(xElementlineThic);
                    xElementline.Add(xElementART);
                    xElementline.Add(xElementRTX);
                    xElementline.Add(xElementRTY);
                    xElementline.Add(xElementSTX);
                    xElementline.Add(xElementSTY);
                    xElementline.Add(xElementASTX);
                    xElementline.Add(xElementASTY);
                    xElementline.Add(xElementPos);

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
                    XElement xElementART = new XElement("angleRT", poly.AngleRT);
                    XElement xElementRTX = new XElement("rtx", poly.RTX);
                    XElement xElementRTY = new XElement("rty", poly.RTY);
                    XElement xElementSTX = new XElement("stx", poly.STX);
                    XElement xElementSTY = new XElement("sty", poly.STY);
                    XElement xElementASTX = new XElement("astx", poly.AngleSTX);
                    XElement xElementASTY = new XElement("asty", poly.AngleSTY);
                    XElement xElementPos = new XElement("pos", poly.Pos);

                    xElementpoly.Add(xAttributeName);
                    xElementpoly.Add(xElementStroke);
                    xElementpoly.Add(xElementThic);
                    xElementpoly.Add(xElementPoint);
                    xElementpoly.Add(xElementART);
                    xElementpoly.Add(xElementRTX);
                    xElementpoly.Add(xElementRTY);
                    xElementpoly.Add(xElementSTX);
                    xElementpoly.Add(xElementSTY);
                    xElementpoly.Add(xElementASTX);
                    xElementpoly.Add(xElementASTY);
                    xElementpoly.Add(xElementPos);

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
                    XElement xElementART = new XElement("angleRT", polygon.AngleRT);
                    XElement xElementRTX = new XElement("rtx", polygon.RTX);
                    XElement xElementRTY = new XElement("rty", polygon.RTY);
                    XElement xElementSTX = new XElement("stx", polygon.STX);
                    XElement xElementSTY = new XElement("sty", polygon.STY);
                    XElement xElementASTX = new XElement("astx", polygon.AngleSTX);
                    XElement xElementASTY = new XElement("asty", polygon.AngleSTY);
                    XElement xElementPos = new XElement("pos", polygon.Pos);

                    xPolygon.Add(xName);
                    xPolygon.Add(xPoint);
                    xPolygon.Add(xStroke);
                    xPolygon.Add(xThic);
                    xPolygon.Add(xFill);
                    xPolygon.Add(xElementART);
                    xPolygon.Add(xElementRTX);
                    xPolygon.Add(xElementRTY);
                    xPolygon.Add(xElementSTX);
                    xPolygon.Add(xElementSTY);
                    xPolygon.Add(xElementASTX);
                    xPolygon.Add(xElementASTY);
                    xPolygon.Add(xElementPos);

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
                    XElement xElementART = new XElement("angleRT", rec.AngleRT);
                    XElement xElementRTX = new XElement("rtx", rec.RTX);
                    XElement xElementRTY = new XElement("rty", rec.RTY);
                    XElement xElementSTX = new XElement("stx", rec.STX);
                    XElement xElementSTY = new XElement("sty", rec.STY);
                    XElement xElementASTX = new XElement("astx", rec.AngleSTX);
                    XElement xElementASTY = new XElement("asty", rec.AngleSTY);

                    xRect.Add(xName);
                    xRect.Add(xPoint);
                    xRect.Add(xWidth);
                    xRect.Add(xHeight);
                    xRect.Add(xThic);
                    xRect.Add(xStroke);
                    xRect.Add(xFill);
                    xRect.Add(xElementART);
                    xRect.Add(xElementRTX);
                    xRect.Add(xElementRTY);
                    xRect.Add(xElementSTX);
                    xRect.Add(xElementSTY);
                    xRect.Add(xElementASTX);
                    xRect.Add(xElementASTY);

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
                    XElement xElementART = new XElement("angleRT", el.AngleRT);
                    XElement xElementRTX = new XElement("rtx", el.RTX);
                    XElement xElementRTY = new XElement("rty", el.RTY);
                    XElement xElementSTX = new XElement("stx", el.STX);
                    XElement xElementSTY = new XElement("sty", el.STY);
                    XElement xElementASTX = new XElement("astx", el.AngleSTX);
                    XElement xElementASTY = new XElement("asty", el.AngleSTY);

                    xElip.Add(xName);
                    xElip.Add(xPoint);
                    xElip.Add(xWidth);
                    xElip.Add(xHeight);
                    xElip.Add(xThic);
                    xElip.Add(xStroke);
                    xElip.Add(xFill);
                    xElip.Add(xElementART);
                    xElip.Add(xElementRTX);
                    xElip.Add(xElementRTY);
                    xElip.Add(xElementSTX);
                    xElip.Add(xElementSTY);
                    xElip.Add(xElementASTX);
                    xElip.Add(xElementASTY);

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
                    XElement xElementART = new XElement("angleRT", pat.AngleRT);
                    XElement xElementRTX = new XElement("rtx", pat.RTX);
                    XElement xElementRTY = new XElement("rty", pat.RTY);
                    XElement xElementSTX = new XElement("stx", pat.STX);
                    XElement xElementSTY = new XElement("sty", pat.STY);
                    XElement xElementASTX = new XElement("astx", pat.AngleSTX);
                    XElement xElementASTY = new XElement("asty", pat.AngleSTY);
                    XElement xElementPos = new XElement("pos", pat.Pos);

                    xPath.Add(xName);
                    xPath.Add(xThic);
                    xPath.Add(xStroke);
                    xPath.Add(xPoint);
                    xPath.Add(xFill);
                    xPath.Add(xElementART);
                    xPath.Add(xElementRTX);
                    xPath.Add(xElementRTY);
                    xPath.Add(xElementSTX);
                    xPath.Add(xElementSTY);
                    xPath.Add(xElementASTX);
                    xPath.Add(xElementASTY);
                    xPath.Add(xElementPos);

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
                    var AngleRT = line.Element("angleRT");
                    var RTX = line.Element("rtx");
                    var RTY = line.Element("rty");
                    var STX = line.Element("stx");
                    var STY = line.Element("sty");
                    var ASTX = line.Element("astx");
                    var ASTY = line.Element("asty");
                    var Pos = line.Element("pos");

                    Gr_Line lin = new Gr_Line(lName.Value, double.Parse(lThic.Value), lStroke.Value, lStart.Value, lEnd.Value);
                    lin.Gr_Line_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                    lin.Pos = Avalonia.Point.Parse(Pos.Value);
                    return lin;
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
                        var AngleRT = poly.Element("angleRT");
                        var RTX = poly.Element("rtx");
                        var RTY = poly.Element("rty");
                        var STX = poly.Element("stx");
                        var STY = poly.Element("sty");
                        var ASTX = poly.Element("astx");
                        var ASTY = poly.Element("asty");
                        var Pos = poly.Element("pos");

                        Gr_PolyLine polyLine = new Gr_PolyLine(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value));
                        polyLine.Gr_Polyline_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                        polyLine.Pos = Avalonia.Point.Parse(Pos.Value);
                        return polyLine;
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
                    var AngleRT = polyg.Element("angleRT");
                    var RTX = polyg.Element("rtx");
                    var RTY = polyg.Element("rty");
                    var STX = polyg.Element("stx");
                    var STY = polyg.Element("sty");
                    var ASTX = polyg.Element("astx");
                    var ASTY = polyg.Element("asty");
                    var Pos = polyg.Element("pos");

                    Gr_Polygon polygon = new Gr_Polygon(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value), pFill.Value);
                    polygon.Gr_Polygon_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                    polygon.Pos = Avalonia.Point.Parse(Pos.Value);
                    return polygon;
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
                    var AngleRT = rect.Element("angleRT");
                    var RTX = rect.Element("rtx");
                    var RTY = rect.Element("rty");
                    var STX = rect.Element("stx");
                    var STY = rect.Element("sty");
                    var ASTX = rect.Element("astx");
                    var ASTY = rect.Element("asty");

                    Gr_Rectangle rectangle = new Gr_Rectangle(rName.Value, rPoint.Value, int.Parse(rWidth.Value), int.Parse(rHeight.Value), double.Parse(rThic.Value), rStroke.Value, rFill.Value);
                    rectangle.Gr_Rectangle_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                    return rectangle;
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
                    var AngleRT = el.Element("angleRT");
                    var RTX = el.Element("rtx");
                    var RTY = el.Element("rty");
                    var STX = el.Element("stx");
                    var STY = el.Element("sty");
                    var ASTX = el.Element("astx");
                    var ASTY = el.Element("asty");

                    Gr_Ellipse ellipse = new Gr_Ellipse(eName.Value, int.Parse(eWidth.Value), int.Parse(eHeight.Value), ePoint.Value, eStroke.Value, double.Parse(eThic.Value), eFill.Value);
                    ellipse.Gr_Ellipse_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                    return ellipse;
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
                    var AngleRT = pa.Element("angleRT");
                    var RTX = pa.Element("rtx");
                    var RTY = pa.Element("rty");
                    var STX = pa.Element("stx");
                    var STY = pa.Element("sty");
                    var ASTX = pa.Element("astx");
                    var ASTY = pa.Element("asty");
                    var Pos = pa.Element("pos");

                    Gr_Path path1 = new Gr_Path(pName.Value, pPoint.Value, pStroke.Value, double.Parse(pThic.Value), pFill.Value);
                    path1.Gr_Path_transform(AngleRT.Value, RTX.Value + " " + RTY.Value, STX.Value + " " + STY.Value, ASTX.Value + " " + ASTY.Value);
                    path1.Pos = Avalonia.Point.Parse(Pos.Value);
                    return path1;
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
