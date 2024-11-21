using ReactiveUI;
using RomanNumbersCalculator.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Net.Http.Headers;
using System.Text;

namespace RomanNumbersCalculator.ViewModels
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        private string currentOperationStringRepresentation = "";
        private string currentNumberStringRepresentation = "";
        public string CurrentNumberRepresentation
        {
            get => currentNumberStringRepresentation;
        }

        public string AddNumber
        {
            set
            {
                if (currentNumberStringRepresentation != "#ERROR")
                {
                    currentNumberStringRepresentation += value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
                }
            }
        }

        public string ResetCommand
        {
            set
            {
                currentNumberStringRepresentation = "";
                currentOperationStringRepresentation = "";
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
            }
        }

        public string PlusCommand
        {
            set
            {
                if(currentNumberStringRepresentation!= "" && currentNumberStringRepresentation != "#ERROR")
                {
                    currentOperationStringRepresentation += value;
                    currentNumberStringRepresentation += value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
                }
                
            }
        }

        public string SubCommand
        {
            set
            {
                if (currentNumberStringRepresentation != "" && currentNumberStringRepresentation != "#ERROR")
                {
                    currentOperationStringRepresentation += value;
                    currentNumberStringRepresentation += value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
                }
            }
        }

        public string MulCommand
        {
            set
            {
                if (currentNumberStringRepresentation != "" && currentNumberStringRepresentation != "#ERROR")
                {
                    currentOperationStringRepresentation += value;
                    currentNumberStringRepresentation += value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
                }
            }
        }

        public string DivCommand
        {
            set
            {
                if (currentNumberStringRepresentation != "" && currentNumberStringRepresentation!="#ERROR")
                {
                    currentOperationStringRepresentation += value;
                    currentNumberStringRepresentation += value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
                }
            }
        }

        public string CalComand
        {
            set
            {
                currentNumberStringRepresentation = value;
                currentOperationStringRepresentation = "";
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CurrentNumberRepresentation)));
            }
        }

        private void ButtonAddClick(string Vvalue) => AddNumber = Vvalue;
        private void ButtonCleClick() => ResetCommand = "";
        private void PlusClick()
        {
            if(currentOperationStringRepresentation=="" && currentNumberStringRepresentation != "#ERROR") PlusCommand = "+";
        }
        private void SubClick()
        {
            if (currentOperationStringRepresentation == "" && currentNumberStringRepresentation != "#ERROR") SubCommand = "-";
        }
        private void MulClick()
        {
            if (currentOperationStringRepresentation == "" && currentNumberStringRepresentation != "#ERROR") MulCommand = "*";
        }
        private void DivClick()
        {
            if (currentOperationStringRepresentation == "" && currentNumberStringRepresentation != "#ERROR") DivCommand = "/";
        }
        private void CalClick()
        {
            if (currentOperationStringRepresentation != "" && currentNumberStringRepresentation != "#ERROR")
            {
                RomanNumberExtend obj = new RomanNumberExtend(currentNumberStringRepresentation);
                obj.chooseOp();
                CalComand = obj.ReturnResult();
            }
        }

        public event PropertyChangedEventHandler? PropertyChanged;
    }
}
