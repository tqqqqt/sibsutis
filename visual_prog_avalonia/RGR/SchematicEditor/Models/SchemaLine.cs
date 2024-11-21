using System;
using System.Collections.ObjectModel;

namespace SchematicEditor.Models
{
    public class SchemaLine : ISchemaObject, IDisposable
    {
        private Avalonia.Point endPoint;
        private ISchemaElement? firstElement, secondElement;
        private int typeFirstElement, typeSecondElement, status, indexFirstElement, indexSecondElement;
        private string nameFirstElement, nameSecondElement;

        public SchemaLine()
        {
            FirstElement = null;
            SecondElement = null;
            TypeFirstElement = 0;
            TypeSecondElement = 0;
            IndexFirstElement = 0;
            IndexSecondElement = 0;
            Status = 0;
            NameFirstElement = string.Empty;
            NameSecondElement = string.Empty;
        }

        public Avalonia.Point StartPoint
        {
            get => startPoint;
            set => SetAndRaise(ref startPoint, value);
        }
        public Avalonia.Point EndPoint
        {
            get => endPoint;
            set => SetAndRaise(ref endPoint, value);
        }

        public ISchemaElement FirstElement
        {
            get => firstElement;
            set
            {
                if (firstElement != null)
                {
                    firstElement.ChangeStartPoint -= OnFirstElementChange;
                    firstElement.ChangeStatus -= OnStatusChange;
                }
                firstElement = value;
                if (firstElement != null)
                {
                    firstElement.ChangeStartPoint += OnFirstElementChange;
                    firstElement.ChangeStatus += OnStatusChange;
                    GetFirstStatus();
                }
            }
        }

        public ISchemaElement SecondElement
        {
            get => secondElement;
            set
            {
                if (secondElement != null)
                {
                    secondElement.ChangeStartPoint -= OnSecondElementChange;
                }
                secondElement = value;
                if (secondElement != null)
                {
                    secondElement.ChangeStartPoint += OnSecondElementChange;
                    GetFirstStatus();
                }
            }
        }

        public int TypeFirstElement
        {
            get => typeFirstElement;
            set => SetAndRaise(ref typeFirstElement, value);
        }

        public int TypeSecondElement
        {
            get => typeSecondElement;
            set => SetAndRaise(ref typeSecondElement, value);
        }

        public int IndexFirstElement
        {
            get => indexFirstElement;
            set => SetAndRaise(ref indexFirstElement, value);
        }

        public int IndexSecondElement
        {
            get => indexSecondElement;
            set => SetAndRaise(ref indexSecondElement, value);
        }

        public string NameFirstElement
        {
            get => nameFirstElement;
            set => SetAndRaise(ref nameFirstElement, value);
        }

        public string NameSecondElement
        {
            get => nameSecondElement;
            set => SetAndRaise(ref nameSecondElement, value);
        }

        public int Status
        {
            get => status;
            set => SetAndRaise(ref status, value);
        }

        private void OnFirstElementChange(object? sender, ChangeStartPointEventArgs e)
        {
            StartPoint += e.NewStartPoint - e.OldStartPoint;
        }

        private void OnSecondElementChange(object? sender, ChangeStartPointEventArgs e)
        {
            EndPoint += e.NewStartPoint - e.OldStartPoint;
        }

        private void OnStatusChange(object? sender, ChangeStatusEventArgs e)
        {
            if (NameFirstElement.Equals("OUT") == true || NameFirstElement.Equals("OUT1")) Status = e.NewStatus;
            else if (NameFirstElement.Equals("OUT2") == true) Status = e.NewStatus2;
            ConectionUpdate();
        }

        private void GetFirstStatus()
        {
            if (NameFirstElement.Equals("OUT") == true || NameFirstElement.Equals("OUT1") == true) Status = FirstElement.OutSignal;
            else if (NameFirstElement.Equals("OUT2") == true) Status = FirstElement.OutSignal2;
            ConectionUpdate();
        }

        public void Dispose()
        {
            if (FirstElement != null)
            {
                FirstElement.ChangeStartPoint -= OnFirstElementChange;
            }
            if (SecondElement != null)
            {
                SecondElement.ChangeStartPoint -= OnSecondElementChange;
            }
        }

        public void ConectionUpdate()
        {
            if (SecondElement is ElementOUT elOut)
            {
                elOut.InSignal = Status;
            }
            else if (SecondElement is ElementAND elAnd)
            {
                if (NameSecondElement.Equals("IN1") == true) elAnd.InSignal1 = Status;
                else elAnd.InSignal2 = Status;
            }
            else if (SecondElement is ElementOR elOr)
            {
                if (NameSecondElement.Equals("IN1") == true) elOr.InSignal1 = Status;
                else elOr.InSignal2 = Status;
            }
            else if (SecondElement is ElementNO elNo)
            {
                elNo.InSignal = Status;
            }
            else if (SecondElement is ElementXOR elXor)
            {
                if (NameSecondElement.Equals("IN1") == true) elXor.InSignal1 = Status;
                else elXor.InSignal2 = Status;
            }
            else if (SecondElement is ElementDE elDe)
            {
                if (NameSecondElement.Equals("IN1") == true) elDe.InSignal1 = Status;
                else elDe.InSignal2 = Status;
            }
        }

        public void LoadConectionUpdate(ObservableCollection<Schema> schemaColection)
        {
            foreach (Schema tempSchema in schemaColection)
            {
                foreach (ISchemaObject tempObject in tempSchema.ElementColection)
                {
                    if (tempObject is SchemaLine tempLine)
                    {
                        int find = 0;
                        foreach (ISchemaObject tempFindObject in tempSchema.ElementColection)
                        {
                            if (tempFindObject is ISchemaElement schemaElement)
                            {
                                if (tempLine.IndexFirstElement == schemaElement.IndexElement)
                                {
                                    tempLine.FirstElement = schemaElement;
                                    find++;
                                }
                                else if (tempLine.IndexSecondElement == schemaElement.IndexElement)
                                {
                                    tempLine.SecondElement = schemaElement;
                                    find++;
                                }
                                if (find == 2) break;
                            }
                        }
                    }
                }
            }
        }
    }
}
