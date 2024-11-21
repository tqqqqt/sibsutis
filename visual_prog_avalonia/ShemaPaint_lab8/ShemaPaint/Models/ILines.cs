using Avalonia.Media;
using System;
using System.Collections.ObjectModel;
using YamlDotNet.Serialization;

namespace ShemaPaint.Models
{
    public abstract class ILines : IFigures, IDisposable
    {
        // same all
        private Avalonia.Point endPoint;
        private El_Class? firstClass;
        private El_Class? secondClass;
        private El_Interface? firstInterface;
        private El_Interface? secondInterface;
        protected string pathCommands = string.Empty, lineType = string.Empty;
        protected string nameFirstClass = string.Empty, nameSecondClass = string.Empty,
            nameFirstInterface = string.Empty, nameSecondInterface = string.Empty;

        // not all
        private Geometry pathPoints;
        private SolidColorBrush fillColor;
        private double rotateAngle;


        // constr 


        // struct option
        [YamlMember(typeof(string))]
        public Avalonia.Point StartPoint
        {
            get => startPoint;
            set => SetAndRaise(ref startPoint, value);
        }
        [YamlMember(typeof(string))]
        public Avalonia.Point EndPoint
        {
            get => endPoint;
            set => SetAndRaise(ref endPoint, value);
        }
        [YamlIgnore]
        public Geometry PathPoints
        {
            get => pathPoints;
            set => SetAndRaise(ref pathPoints, value);
        }
        [YamlIgnore]
        public SolidColorBrush FillColor
        {
            get => fillColor;
            set => SetAndRaise(ref fillColor, value);
        }
        [YamlMember(typeof(string))]
        public string PathCommands
        {
            get => pathCommands;
            set => SetAndRaise(ref pathCommands, value);
        }
        [YamlMember(typeof(string))]
        public string LineType
        {
            get => lineType;
            set => SetAndRaise(ref lineType, value);
        }
        [YamlMember(typeof(string))]
        public string NameFirstClass
        {
            get => nameFirstClass;
            set => SetAndRaise(ref nameFirstClass, value);
        }
        [YamlMember(typeof(string))]
        public string NameSecondClass
        {
            get => nameSecondClass;
            set => SetAndRaise(ref nameSecondClass, value);
        }
        [YamlMember(typeof(string))]
        public string NameFirstInterface
        {
            get => nameFirstInterface;
            set => SetAndRaise(ref nameFirstInterface, value);
        }
        [YamlMember(typeof(string))]
        public string NameSecondInterface
        {
            get => nameSecondInterface;
            set => SetAndRaise(ref nameSecondInterface, value);
        }
        [YamlMember(typeof(double))]
        public double RotateAngle
        {
            get => rotateAngle;
            set => SetAndRaise(ref rotateAngle, value);
        }

        // link option
        [YamlIgnore]
        public El_Class FirstClass
        {
            get => firstClass;
            set
            {
                if (firstClass != null)
                {
                    firstClass.ChangeStartPoint -= OnFirstClassPosChange;
                }
                firstClass = value;
                if (firstClass != null)
                {
                    firstClass.ChangeStartPoint += OnFirstClassPosChange;
                    NameFirstClass = firstClass.Name;
                }
            }
        }
        [YamlIgnore]
        public El_Class SecondClass
        {
            get => secondClass;
            set
            {
                if (secondClass != null)
                {
                    secondClass.ChangeStartPoint -= OnSecondClassPosChange;
                }
                secondClass = value;
                if (secondClass != null)
                {
                    secondClass.ChangeStartPoint += OnSecondClassPosChange;
                    NameSecondClass = secondClass.Name;
                }
            }
        }
        [YamlIgnore]
        public El_Interface FirstInterface
        {
            get => firstInterface;
            set
            {
                if (firstInterface != null)
                {
                    firstInterface.ChangeStartPoint -= OnFirstInterfacePosChange;
                }
                firstInterface = value;
                if (firstInterface != null)
                {
                    firstInterface.ChangeStartPoint += OnFirstInterfacePosChange;
                    NameFirstInterface = firstInterface.Name;
                }
            }
        }
        [YamlIgnore]
        public El_Interface SecondInterface
        {
            get => secondInterface;
            set
            {
                if (secondInterface != null)
                {
                    secondInterface.ChangeStartPoint -= OnSecondInterfacePosChange;
                }
                secondInterface = value;
                if (secondInterface != null)
                {
                    secondInterface.ChangeStartPoint += OnSecondInterfacePosChange;
                    NameSecondInterface = secondInterface.Name;
                }
            }
        }


        // function
        public void PathUpdate()
        {
            string fullPathCommands = "M " + Math.Ceiling(EndPoint.X).ToString() + "," + Math.Ceiling(EndPoint.Y).ToString() + pathCommands;
            PathPoints = Geometry.Parse(fullPathCommands);
            var delta = StartPoint - EndPoint;
            double newDig = Math.Sqrt(Math.Pow(delta.X, 2) + Math.Pow(delta.Y, 2));
            double origDig = newDig > 0 ? newDig : 0.001;
            double angle = Math.Acos(delta.X / origDig);
            angle = angle * 180 / Math.PI;
            if (delta.Y < 0) angle = 360 - angle;
            angle = (angle + 180) % 360;
            RotateAngle = angle;
        }
        public void ConnectUpdate(ObservableCollection<IFigures> curentColection)
        {
            for (int i = curentColection.Count - 1; i >= 0; i--)
            {
                if (curentColection[i] is ILines curentLine)
                {
                    int findConection = 0;
                    for (int j = 0; j < curentColection.Count; j++)
                    {
                        if (j == i) continue;
                        if (curentColection[j] is El_Class curentClass)
                        {
                            if (curentClass.Name == curentLine.NameFirstClass)
                            {
                                curentLine.FirstClass = curentClass;
                                findConection++;
                            }
                            if (curentClass.Name == curentLine.NameSecondClass)
                            {
                                curentLine.SecondClass = curentClass;
                                findConection++;
                            }
                        }
                        if (curentColection[j] is El_Interface curentInterface)
                        {
                            if (curentInterface.Name == curentLine.NameFirstInterface)
                            {
                                curentLine.FirstInterface = curentInterface;
                                findConection++;
                            }
                            if (curentInterface.Name == curentLine.NameSecondInterface)
                            {
                                curentLine.SecondInterface = curentInterface;
                                findConection++;
                            }
                        }
                        if (findConection == 2) break;
                    }
                }
            }
        }


        // link function
        private void OnFirstClassPosChange(object? sender, ChangeStartPointEventArgs e)
        {
            StartPoint += e.NewStartPoint - e.OldStartPoint;
            PathUpdate();
        }
        private void OnSecondClassPosChange(object? sender, ChangeStartPointEventArgs e)
        {
            EndPoint += e.NewStartPoint - e.OldStartPoint;
            PathUpdate();
        }
        private void OnFirstInterfacePosChange(object? sender, ChangeStartPointEventArgs e)
        {
            StartPoint += e.NewStartPoint - e.OldStartPoint;
            PathUpdate();
        }
        private void OnSecondInterfacePosChange(object? sender, ChangeStartPointEventArgs e)
        {
            EndPoint += e.NewStartPoint - e.OldStartPoint;
            PathUpdate();
        }

        public void Dispose()
        {
            if (FirstClass != null)
            {
                FirstClass.ChangeStartPoint -= OnFirstClassPosChange;
                NameFirstClass = string.Empty;
            }
            if (SecondClass != null)
            {
                SecondClass.ChangeStartPoint -= OnSecondClassPosChange;
                NameSecondClass = string.Empty;
            }
            if (FirstInterface != null)
            {
                FirstInterface.ChangeStartPoint -= OnFirstInterfacePosChange;
                NameFirstInterface = string.Empty;
            }
            if (SecondInterface != null)
            {
                SecondInterface.ChangeStartPoint -= OnSecondInterfacePosChange;
                NameSecondInterface = string.Empty;
            }
        }
    }
}
