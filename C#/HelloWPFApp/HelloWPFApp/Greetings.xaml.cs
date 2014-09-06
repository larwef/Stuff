using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace HelloWPFApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (RadioButton1.IsChecked == true)
            {
                MessageBox.Show("Hello.");
            }
            else
            {
                RadioButton2.IsChecked = true;
                MessageBox.Show("Goodbye.");
            }
        }

        async private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            btn2.IsEnabled = false;
            for (int i = 0; i < 10; i++)
            {
                textBox.Text = i.ToString();
                rectangle.Height += i;
                await Task.Delay(1000);
            }
            btn2.IsEnabled = true;
        }
    }
}
