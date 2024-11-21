using System;
using System.Collections.ObjectModel;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace ShemaPaint.Models
{
    public class ELementsJsonConverter : JsonConverter<IFigures>
    {
        public override IFigures? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
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
                if (typeName != null && (typeName.Equals("class") || typeName.Equals("interface")))
                {
                    reader.Read();
                    string? nameProperty = reader.GetString();
                    reader.Read();
                    string? nameValue = reader.GetString();
                    reader.Read();
                    string? sterProperty = reader.GetString();
                    reader.Read();
                    string? sterValue = reader.GetString();
                    reader.Read();
                    string? vidProperty = reader.GetString();
                    reader.Read();
                    string? vidValue = reader.GetString();
                    reader.Read();
                    string? startProperty = reader.GetString();
                    reader.Read();
                    string? startValue = reader.GetString();
                    reader.Read();
                    string? mainFontProperty = reader.GetString();
                    reader.Read();
                    string? mainFontValue = reader.GetString();
                    reader.Read();
                    string? widthProperty = reader.GetString();
                    reader.Read();
                    string? widthValue = reader.GetString();
                    reader.Read();
                    string? heightProperty = reader.GetString();
                    reader.Read();
                    string? heightValue = reader.GetString();
                    reader.Read();
                    string? atCountProperty = reader.GetString();
                    reader.Read();
                    string? atCountValue = reader.GetString();
                    reader.Read();
                    string? opCountProperty = reader.GetString();
                    reader.Read();
                    string? opCountValue = reader.GetString();
                    ObservableCollection<Atrib> loadAtribColection = new ObservableCollection<Atrib>();
                    for (int i = 0; i < int.Parse(atCountValue); i++)
                    {
                        reader.Read();
                        string? atNameProperty = reader.GetString();
                        reader.Read();
                        string? atNameValue = reader.GetString();
                        reader.Read();
                        string? atTypeProperty = reader.GetString();
                        reader.Read();
                        string? atTypeValue = reader.GetString();
                        reader.Read();
                        string? atVidProperty = reader.GetString();
                        reader.Read();
                        string? atVidValue = reader.GetString();
                        reader.Read();
                        string? atSterProperty = reader.GetString();
                        reader.Read();
                        string? atSterValue = reader.GetString();
                        reader.Read();
                        string? atValueProperty = reader.GetString();
                        reader.Read();
                        string? atValueValue = reader.GetString();
                        Atrib atribElement = new Atrib
                        {
                            Name = atNameValue,
                            Type = atTypeValue,
                            Vidim = atVidValue,
                            Stereot = atSterValue,
                            AtribValue = atValueValue,
                        };
                        loadAtribColection.Add(atribElement);
                    }
                    ObservableCollection<Oper> loadOperColection = new ObservableCollection<Oper>();
                    for (int i = 0; i < int.Parse(opCountValue); i++)
                    {
                        reader.Read();
                        string? opNameProperty = reader.GetString();
                        reader.Read();
                        string? opNameValue = reader.GetString();
                        reader.Read();
                        string? opTypeProperty = reader.GetString();
                        reader.Read();
                        string? opTypeValue = reader.GetString();
                        reader.Read();
                        string? opVidProperty = reader.GetString();
                        reader.Read();
                        string? opVidValue = reader.GetString();
                        reader.Read();
                        string? opSterProperty = reader.GetString();
                        reader.Read();
                        string? opSterValue = reader.GetString();
                        reader.Read();
                        string? parNameProperty = reader.GetString();
                        reader.Read();
                        string? parNameValue = reader.GetString();
                        reader.Read();
                        string? parTypeProperty = reader.GetString();
                        reader.Read();
                        string? parTypeValue = reader.GetString();
                        Oper operElement = new Oper
                        {
                            OpName = opNameValue,
                            OpType = opTypeValue,
                            OpVidim = opVidValue,
                            OpSter = opSterValue,
                            ParName = parNameValue,
                            ParType = parTypeValue,
                        };
                        loadOperColection.Add(operElement);
                    }
                    if (typeName.Equals("class"))
                    {
                        El_Class classElement = new El_Class
                        {
                            Name = nameValue,
                            Stereotip = sterValue,
                            Vidimost = vidValue,
                            StartPoint = Avalonia.Point.Parse(startValue),
                            FontSizeMain = double.Parse(mainFontValue),
                            Width = double.Parse(widthValue),
                            Height = double.Parse(heightValue),
                            Atrib_colection = loadAtribColection,
                            Oper_colection = loadOperColection,
                        };
                        reader.Read();
                        return classElement;
                    }
                    else if (typeName.Equals("interface"))
                    {
                        El_Interface interfaceElement = new El_Interface
                        {
                            Name = nameValue,
                            Stereotip = sterValue,
                            Vidimost = vidValue,
                            StartPoint = Avalonia.Point.Parse(startValue),
                            FontSizeMain = double.Parse(mainFontValue),
                            Width = double.Parse(widthValue),
                            Height = double.Parse(heightValue),
                            AtribColection = loadAtribColection,
                            OperColection = loadOperColection,
                        };
                        reader.Read();
                        return interfaceElement;
                    }
                }
                if (typeName != null && typeName.Equals("line"))
                {
                    reader.Read();
                    string? lineTypeProperty = reader.GetString();
                    reader.Read();
                    string? lineTypeValue = reader.GetString();
                    reader.Read();
                    string? lineStartProperty = reader.GetString();
                    reader.Read();
                    string? lineStartValue = reader.GetString();
                    reader.Read();
                    string? lineEndProperty = reader.GetString();
                    reader.Read();
                    string? lineEndValue = reader.GetString();
                    reader.Read();
                    string? lineFirstClassProperty = reader.GetString();
                    reader.Read();
                    string? lineFirstClassValue = reader.GetString();
                    reader.Read();
                    string? lineSecondClassProperty = reader.GetString();
                    reader.Read();
                    string? lineSecondClassValue = reader.GetString();
                    reader.Read();
                    string? lineFirstInterfaceProperty = reader.GetString();
                    reader.Read();
                    string? lineFirstInterfaceValue = reader.GetString();
                    reader.Read();
                    string? lineSecondInterfaceProperty = reader.GetString();
                    reader.Read();
                    string? lineSecondInterfaceValue = reader.GetString();
                    ILines? lineElement = null;
                    if (lineTypeValue.Equals("Nasled"))
                    {
                        lineElement = new LineNasled
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    else if (lineTypeValue.Equals("Realiz"))
                    {
                        lineElement = new LineRealiz
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    else if (lineTypeValue.Equals("Zavis"))
                    {
                        lineElement = new LineZavis
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    else if (lineTypeValue.Equals("Agreg"))
                    {
                        lineElement = new LineAgreg
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    else if (lineTypeValue.Equals("Compos"))
                    {
                        lineElement = new LineCompos
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    else if (lineTypeValue.Equals("Acos"))
                    {
                        lineElement = new LineAsoc
                        {
                            StartPoint = Avalonia.Point.Parse(lineStartValue),
                            EndPoint = Avalonia.Point.Parse(lineEndValue),
                        };
                    }
                    if (lineElement != null)
                    {
                        if (lineFirstClassValue != null) lineElement.NameFirstClass = lineFirstClassValue;
                        if (lineSecondClassValue != null) lineElement.NameSecondClass = lineSecondClassValue;
                        if (lineFirstInterfaceValue != null) lineElement.NameFirstInterface = lineFirstInterfaceValue;
                        if (lineSecondInterfaceValue != null) lineElement.NameSecondInterface = lineSecondInterfaceValue;
                        lineElement.PathUpdate();
                        reader.Read();
                        return lineElement;
                    }
                }
            }
            else
            {
                throw new JsonException("Missed type property");
            }
            return null;
        }

        public override void Write(Utf8JsonWriter writer, IFigures value, JsonSerializerOptions options)
        {
            writer.WriteStartObject();
            if (value is El_Class classElement)
            {
                writer.WriteString("type", "class");
                writer.WriteString("name", classElement.Name);
                writer.WriteString("ster", classElement.Stereotip);
                writer.WriteString("vid", classElement.Vidimost);
                writer.WriteString("start", ((int)classElement.StartPoint.X).ToString() + " , " + ((int)classElement.StartPoint.Y).ToString());
                writer.WriteString("mainFont", classElement.FontSizeMain.ToString());
                writer.WriteString("width", classElement.Width.ToString());
                writer.WriteString("height", classElement.Height.ToString());
                writer.WriteString("atCount", classElement.Atrib_colection.Count.ToString());
                writer.WriteString("opCount", classElement.Oper_colection.Count.ToString());
                foreach (Atrib atrib in classElement.Atrib_colection)
                {
                    writer.WriteString("name", atrib.Name);
                    writer.WriteString("atType", atrib.Type);
                    writer.WriteString("vid", atrib.Vidim);
                    writer.WriteString("ster", atrib.Stereot);
                    writer.WriteString("value", atrib.AtribValue);
                }
                foreach (Oper oper in classElement.Oper_colection)
                {
                    writer.WriteString("name", oper.OpName);
                    writer.WriteString("opType", oper.OpType);
                    writer.WriteString("vid", oper.OpVidim);
                    writer.WriteString("ster", oper.OpSter);
                    writer.WriteString("parName", oper.ParName);
                    writer.WriteString("parType", oper.ParType);
                }
            }
            if (value is El_Interface interfaceElement)
            {
                writer.WriteString("type", "interface");
                writer.WriteString("name", interfaceElement.Name);
                writer.WriteString("ster", interfaceElement.Stereotip);
                writer.WriteString("vid", interfaceElement.Vidimost);
                writer.WriteString("start", ((int)interfaceElement.StartPoint.X).ToString() + " , " + ((int)interfaceElement.StartPoint.Y).ToString());
                writer.WriteString("mainfFont", interfaceElement.FontSizeMain.ToString());
                writer.WriteString("width", interfaceElement.Width.ToString());
                writer.WriteString("height", interfaceElement.Height.ToString());
                writer.WriteString("atCount", interfaceElement.AtribColection.Count.ToString());
                writer.WriteString("opCount", interfaceElement.OperColection.Count.ToString());
                foreach (Atrib atrib in interfaceElement.AtribColection)
                {
                    writer.WriteString("name", atrib.Name);
                    writer.WriteString("atType", atrib.Type);
                    writer.WriteString("vid", atrib.Vidim);
                    writer.WriteString("ster", atrib.Stereot);
                    writer.WriteString("value", atrib.AtribValue);
                }
                foreach (Oper oper in interfaceElement.OperColection)
                {
                    writer.WriteString("name", oper.OpName);
                    writer.WriteString("opType", oper.OpType);
                    writer.WriteString("vid", oper.OpVidim);
                    writer.WriteString("ster", oper.OpSter);
                    writer.WriteString("parName", oper.ParName);
                    writer.WriteString("parType", oper.ParType);
                }
            }
            if (value is ILines linesElement)
            {
                writer.WriteString("type", "line");
                writer.WriteString("lineType", linesElement.LineType);
                writer.WriteString("start", ((int)linesElement.StartPoint.X).ToString() + " , " + ((int)linesElement.StartPoint.Y).ToString());
                writer.WriteString("end", ((int)linesElement.EndPoint.X).ToString() + " , " + ((int)linesElement.EndPoint.Y).ToString());
                writer.WriteString("firstClass", linesElement.NameFirstClass);
                writer.WriteString("secondClass", linesElement.NameSecondClass);
                writer.WriteString("firstInterface", linesElement.NameFirstInterface);
                writer.WriteString("secondInterface", linesElement.NameSecondInterface);
            }
            writer.WriteEndObject();
        }
    }
}
