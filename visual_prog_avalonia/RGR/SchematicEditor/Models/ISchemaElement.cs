using System;

namespace SchematicEditor.Models
{
    public class ISchemaElement : ISchemaObject
    {
        private int indexElement;
        protected int outSignal, outSignal2;

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
                        NewStartPoint = StartPoint
                    };
                    ChangeStartPoint(this, args);
                }
            }
        }

        public int OutSignal
        {
            get => outSignal;
            set
            {
                SetAndRaise(ref outSignal, value);
                if (ChangeStatus != null)
                {
                    ChangeStatusEventArgs args = new ChangeStatusEventArgs
                    {
                        NewStatus = OutSignal,
                        NewStatus2 = OutSignal2,
                    };
                    ChangeStatus(this, args);
                }
            }
        }

        public int OutSignal2
        {
            get => outSignal2;
            set
            {
                SetAndRaise(ref outSignal2, value);
                if (ChangeStatus != null)
                {
                    ChangeStatusEventArgs args = new ChangeStatusEventArgs
                    {
                        NewStatus = OutSignal,
                        NewStatus2 = OutSignal2,
                    };
                    ChangeStatus(this, args);
                }
            }
        }

        public int IndexElement
        {
            get => indexElement;
            set => SetAndRaise(ref indexElement, value);
        }

        public event EventHandler<ChangeStartPointEventArgs> ChangeStartPoint;
        public event EventHandler<ChangeStatusEventArgs> ChangeStatus;
    }
}
