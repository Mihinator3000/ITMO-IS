using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace AutoClicker
{
    public partial class MainWindow : Window
    {
        private bool ActionInProgress = false;
        private LowLevelKeyboardListener Listener;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Listener = new LowLevelKeyboardListener();
            Listener.OnKeyPressed += ListenerOnKeyPressed;
            Listener.HookKeyboard();
        }

        void ListenerOnKeyPressed(object sender, KeyPressedArgs e)
        {
            if (e.KeyPressed == Key.F9)
            {
                AsyncMouseClick();
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Listener.UnHookKeyboard();
        }

        private void StartStop_Click(object sender, RoutedEventArgs e)
        {
            AsyncMouseClick();
        }
        private async void AsyncMouseClick()
        {
            if ((StartStop.Content).ToString().Contains("Start"))
            {
                bool correct = true;
                if (!int.TryParse(DurationTextBox.Text, out int duration) || 
                    duration < -1)
                {
                        MessageBox.Show("Incorrect duration input");
                        correct = false;
                }
                if (!int.TryParse(ClicksTextBox.Text, out int clicksPerSecond) || 
                    clicksPerSecond < 1 || 
                    clicksPerSecond > 100)
                {
                    MessageBox.Show("Incorrect c/s input");
                    correct = false;
                }
                int x = 0, y = 0;
                bool current = (bool)CurBox.IsChecked;
                if (!current)
                {
                    if (!int.TryParse(XTextBox.Text, out x) ||
                       !int.TryParse(YTextBox.Text, out y) || 
                       x < 0 ||
                       y < 0)
                    {
                        MessageBox.Show("Incorrect coordinates input");
                        correct = false;
                    }
                }

                if (!correct)
                    return;

                StartStop.Content = "Stop (F9)";
                StartStop.Background = (SolidColorBrush)new BrushConverter().ConvertFrom("#FFF71919");
                ActionInProgress = true;
                await Task.Run(()
                    => 
                MouseClick(
                    duration,
                    clicksPerSecond,
                    current,
                    x,
                    y));
            }
            else
            {
                ActionInProgress = false;
            }
            StartStop.Content = "Start (F9)";
            StartStop.Background = (SolidColorBrush)new BrushConverter().ConvertFrom("#FF59F109");
        }
        
        private void MouseClick(int duration, int clicksPerSecond, bool current, int x, int y)
        {
            var startPos = MouseClicks.GetCursorPosition();
            int sleepTime = 1000 / clicksPerSecond;
            int cycles = (int)(clicksPerSecond * ((double)duration / 1000));
            for (int i = 0; i < cycles; i++)
            {
                if (!ActionInProgress)
                    break;
                if (!current)
                    MouseClicks.SetCursorPosition(x, y);
                Thread.Sleep(1);
                MouseClicks.MouseEvent(MouseClicks.MouseEventFlags.LeftDown);
                MouseClicks.MouseEvent(MouseClicks.MouseEventFlags.LeftUp);
                Thread.Sleep(sleepTime - 3);
            }
            if (!current)
                MouseClicks.SetCursorPosition(startPos);
        }

        private void Cur_Checked(object sender, RoutedEventArgs e)
        {
            Coordinates.Visibility = Visibility.Hidden;
        }

        private void Cur_Unchecked(object sender, RoutedEventArgs e)
        {
            Coordinates.Visibility = Visibility.Visible;
        }
    }
}
