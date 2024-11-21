using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Graphic.Models
{
    public class ShapeJsonConverter : JsonConverter<IFigure>
    {
        public override IFigure? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType != JsonTokenType.StartObject)
            {
                throw new JsonException("Missed StartObject token");
            }

            reader.Read();
            string? propertyName = reader.GetString();
            if (propertyName != null && propertyName.Equals("type"))
            {
                reader.Read();
                string? typeName = reader.GetString();

                if (typeName != null && typeName.Equals("Line"))
                {
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? nameValue = reader.GetString();
                    reader.Read();
                    string? strokeThicknessProperty = reader.GetString();
                    reader.Read();
                    string? strokeThicknessValue = reader.GetString();
                    reader.Read();
                    string? strokeColorProperty = reader.GetString();
                    reader.Read();
                    string? strokeColorValue = reader.GetString();
                    reader.Read();
                    string? startPointProperty = reader.GetString();
                    reader.Read();
                    string? startPointValue = reader.GetString();
                    reader.Read();
                    string? endPointProperty = reader.GetString();
                    reader.Read();
                    string? endPointValue = reader.GetString();

                    Gr_Line line = new Gr_Line(nameValue, int.Parse(strokeThicknessValue), strokeColorValue, startPointValue, endPointValue);
                    reader.Read();
                    return line;
                }
                if (typeName != null && typeName.Equals("PolyLine"))
                {
                    reader.Read();
                    string? n = reader.GetString();
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? s = reader.GetString();
                    reader.Read();
                    string? thic = reader.GetString();
                    reader.Read();
                    string? ss = reader.GetString();
                    reader.Read();
                    string? stroke_color = reader.GetString();
                    reader.Read();
                    string? p = reader.GetString();
                    reader.Read();
                    string? points = reader.GetString();

                    Gr_PolyLine poly = new Gr_PolyLine(name, points, stroke_color, double.Parse(thic));
                    reader.Read();
                    return poly;
                }
                if (typeName != null && typeName.Equals("Rectangle"))
                {
                    reader.Read();
                    string? n = reader.GetString();
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? s = reader.GetString();
                    reader.Read();
                    string? thic = reader.GetString();
                    reader.Read();
                    string? ss = reader.GetString();
                    reader.Read();
                    string? stroke_color = reader.GetString();
                    reader.Read();
                    string? w = reader.GetString();
                    reader.Read();
                    string? width = reader.GetString();
                    reader.Read();
                    string? h = reader.GetString();
                    reader.Read();
                    string? height = reader.GetString();
                    reader.Read();
                    string? f = reader.GetString();
                    reader.Read();
                    string? fill = reader.GetString();
                    reader.Read();
                    string? p = reader.GetString();
                    reader.Read();
                    string? startpoint = reader.GetString();

                    Gr_Rectangle rectangle = new Gr_Rectangle(name, startpoint, double.Parse(width), double.Parse(height), double.Parse(thic), stroke_color, fill);
                    reader.Read();
                    return rectangle;
                }
                if (typeName != null && typeName.Equals("Polygon"))
                {
                    reader.Read();
                    string? n = reader.GetString();
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? s = reader.GetString();
                    reader.Read();
                    string? thic = reader.GetString();
                    reader.Read();
                    string? ss = reader.GetString();
                    reader.Read();
                    string? stroke_color = reader.GetString();
                    reader.Read();
                    string? f = reader.GetString();
                    reader.Read();
                    string? fill = reader.GetString();
                    reader.Read();
                    string? p = reader.GetString();
                    reader.Read();
                    string? points = reader.GetString();

                    Gr_Polygon polygon = new Gr_Polygon(name, points, stroke_color, double.Parse(thic), fill);
                    reader.Read();
                    return polygon;
                }
                if (typeName != null && typeName.Equals("Ellipse"))
                {
                    reader.Read();
                    string? n = reader.GetString();
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? s = reader.GetString();
                    reader.Read();
                    string? thic = reader.GetString();
                    reader.Read();
                    string? ss = reader.GetString();
                    reader.Read();
                    string? stroke_color = reader.GetString();
                    reader.Read();
                    string? f = reader.GetString();
                    reader.Read();
                    string? fill = reader.GetString();
                    reader.Read();
                    string? w = reader.GetString();
                    reader.Read();
                    string? width = reader.GetString();
                    reader.Read();
                    string? h = reader.GetString();
                    reader.Read();
                    string? height = reader.GetString();
                    reader.Read();
                    string? p = reader.GetString();
                    reader.Read();
                    string? startpoint = reader.GetString();

                    Gr_Ellipse ellipse = new Gr_Ellipse(name, int.Parse(width), int.Parse(height), startpoint, stroke_color, double.Parse(thic), fill);
                    reader.Read();
                    return ellipse;
                }
                if (typeName != null && typeName.Equals("Path"))
                {
                    reader.Read();
                    string? n = reader.GetString();
                    reader.Read();
                    string? name = reader.GetString();
                    reader.Read();
                    string? s = reader.GetString();
                    reader.Read();
                    string? thic = reader.GetString();
                    reader.Read();
                    string? ss = reader.GetString();
                    reader.Read();
                    string? stroke_color = reader.GetString();
                    reader.Read();
                    string? f = reader.GetString();
                    reader.Read();
                    string? fill = reader.GetString();
                    reader.Read();
                    string? p = reader.GetString();
                    reader.Read();
                    string? points = reader.GetString();

                    Gr_Path path = new Gr_Path(name, points, stroke_color, double.Parse(thic), fill);
                    reader.Read();
                    return path;
                }
            }
            else
            {
                throw new JsonException("Missed type property");
            }

            return null;
        }

        public override void Write(Utf8JsonWriter writer, IFigure value, JsonSerializerOptions options)
        {
            writer.WriteStartObject();

            if (value is Gr_Line line)
            {
                writer.WriteString("type", "Line");
                writer.WriteString("Name", line.Name);
                writer.WriteString("StrokeThic", line.StrokeThic.ToString());
                writer.WriteString("StrokeColor", line.StrokeColor.ToString());
                writer.WriteString("StartPoint", line.StartPoint.X.ToString() + "," + line.StartPoint.Y.ToString());
                writer.WriteString("EndPoint", line.EndPoint.X.ToString() + "," + line.EndPoint.Y.ToString());
            }
            if (value is Gr_PolyLine poly)
            {
                writer.WriteString("type", "PolyLine");
                writer.WriteString("Name", poly.Name);
                writer.WriteString("StrokeThic", poly.StrokeThic.ToString());
                writer.WriteString("StrokeColor", poly.StrokeColor.ToString());
                writer.WriteString("Points", poly.save_point);
            }
            if (value is Gr_Rectangle rec)
            {
                writer.WriteString("type", "Rectangle");
                writer.WriteString("Name", rec.Name);
                writer.WriteString("StrokeThic", rec.StrokeThic.ToString());
                writer.WriteString("StrokeColor", rec.StrokeColor.ToString());
                writer.WriteString("Width", rec.Width.ToString());
                writer.WriteString("Height", rec.Height.ToString());
                writer.WriteString("Fill", rec.Fill.ToString());
                writer.WriteString("StartPoint", rec.Start_point.X.ToString() + "," + rec.Start_point.Y.ToString());
            }
            if (value is Gr_Polygon pol)
            {
                writer.WriteString("type", "Polygon");
                writer.WriteString("Name", pol.Name);
                writer.WriteString("StrokeThic", pol.StrokeThic.ToString());
                writer.WriteString("StrokeColor", pol.StrokeColor.ToString());
                writer.WriteString("Fill", pol.Fill.ToString());
                writer.WriteString("Points", pol.save_point);
            }
            if (value is Gr_Ellipse el)
            {
                writer.WriteString("type", "Ellipse");
                writer.WriteString("Name", el.Name);
                writer.WriteString("StrokeThic", el.StrokeThic.ToString());
                writer.WriteString("StrokeColor", el.StrokeColor.ToString());
                writer.WriteString("Fill", el.Fill.ToString());
                writer.WriteString("Width", el.Width.ToString());
                writer.WriteString("Height", el.Height.ToString());
                writer.WriteString("StartPoint", el.StartPoint.X.ToString() + "," + el.StartPoint.Y.ToString());
            }
            if (value is Gr_Path pa)
            {
                writer.WriteString("type", "Path");
                writer.WriteString("Name", pa.Name);
                writer.WriteString("StrokeThic", pa.StrokeThic.ToString());
                writer.WriteString("StrokeColor", pa.StrokeColor.ToString());
                writer.WriteString("Fill", pa.Fill.ToString());
                writer.WriteString("Points", pa.save_points);
            }

            writer.WriteEndObject();
        }
    }
}
