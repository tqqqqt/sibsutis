using Avalonia.Media;

namespace ShemaPaint.Models
{
    public class LineCompos : ILines
    {
        private readonly string fillPath = "Black";
        private readonly string needPathData = " l -20,-20 l -20,20 l 20,20 l 20,-20";
        private readonly string needLineType = "Compos";

        public LineCompos()
        {
            PathCommands = needPathData;
            LineType = needLineType;
            PathPoints = Geometry.Parse("m 0,0 z");
            FillColor = SolidColorBrush.Parse(fillPath);
        }
    }
}
