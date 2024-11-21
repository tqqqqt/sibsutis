using System;
using YamlDotNet.Serialization;

namespace ShemaPaint.Models
{
    public abstract class IElements : IFigures
    {
        // struct
        private double height, width;
        private double fontSizeMain, fontSizeAt, fontSizeOp;

        // first lvl
        private string name = string.Empty;
        private string stereotip = string.Empty;
        private string vidimost = string.Empty;


        // struct
        [YamlMember(typeof(double))]
        public double Height
        {
            get => height;
            set => SetAndRaise(ref height, value);
        }
        [YamlMember(typeof(double))]
        public double Width
        {
            get => width;
            set => SetAndRaise(ref width, value);
        }
        [YamlMember(typeof(double))]
        public double FontSizeMain
        {
            get => fontSizeMain;
            set => SetAndRaise(ref fontSizeMain, value);
        }
        [YamlMember(typeof(double))]
        public double FontSizeAt
        {
            get => fontSizeAt;
            set => SetAndRaise(ref fontSizeAt, value);
        }
        [YamlMember(typeof(double))]
        public double FontSizeOp
        {
            get => fontSizeOp;
            set => SetAndRaise(ref fontSizeOp, value);
        }
        [YamlMember(typeof(string))]
        public Avalonia.Point StartPoint
        {
            get => startPoint;
            set
            {
                Avalonia.Point oldPoint = StartPoint;
                SetAndRaise(ref startPoint, value);
                if (ChangeStartPoint != null)
                {
                    ChangeStartPointEventArgs args = new ChangeStartPointEventArgs
                    {
                        OldStartPoint = oldPoint,
                        NewStartPoint = StartPoint,
                    };
                    ChangeStartPoint(this, args);
                }
            }
        }


        // first
        [YamlMember(typeof(string))]
        public string Name
        {
            get => name;
            set => SetAndRaise(ref name, value);
        }
        [YamlMember(typeof(string))]
        public string Stereotip
        {
            get => stereotip;
            set => SetAndRaise(ref stereotip, value);
        }
        [YamlMember(typeof(string))]
        public string Vidimost
        {
            get => vidimost;
            set => SetAndRaise(ref vidimost, value);
        }


        public event EventHandler<ChangeStartPointEventArgs> ChangeStartPoint;
    }
}
