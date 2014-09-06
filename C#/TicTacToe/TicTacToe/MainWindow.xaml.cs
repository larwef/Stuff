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

namespace TicTacToe
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        static int player = 1;
        static int[,] score = new int[3,3];

        private void click(object sender, MouseButtonEventArgs e)
        {
            var box = (sender as TextBlock);
            if(player == 1 && box.Background == Brushes.White) {
                box.Background = Brushes.Red;

                string place = box.Name.Remove(0, 3);
                score[(int)Char.GetNumericValue(place[0]), (int)Char.GetNumericValue(place[1])] = player;

                player = 2;
            }
            else if (player == 2 && box.Background == Brushes.White) {
                box.Background = Brushes.Blue;

                string place = box.Name.Remove(0, 3);
                score[(int)Char.GetNumericValue(place[0]), (int)Char.GetNumericValue(place[1])] = player;

                player = 1;
            }
            CheckForWin();
        }

        //This is bad...
        public void CheckForWin()
        {
            // For red
            if(score[0, 0] == 1 && score[0, 1] == 1 && score[0, 2] == 1 ||
                score[1, 0] == 1 && score[1, 1] == 1 && score[1, 2] == 1 ||
                score[2, 0] == 1 && score[2, 1] == 1 && score[2, 2] == 1 ||
                score[0, 0] == 1 && score[1, 0] == 1 && score[2, 0] == 1 ||
                score[0, 1] == 1 && score[1, 1] == 1 && score[2, 1] == 1 ||
                score[0, 2] == 1 && score[1, 2] == 1 && score[2, 2] == 1 ||
                score[0, 0] == 1 && score[1, 1] == 1 && score[2, 2] == 1 ||
                score[2, 0] == 1 && score[1, 1] == 1 && score[0, 2] == 1) {
                MessageBox.Show("Red won!");
                Application.Current.Shutdown();
                
            }
            // For blue
            if (score[0, 0] == 2 && score[0, 1] == 2 && score[0, 2] == 2 ||
                score[1, 0] == 2 && score[1, 1] == 2 && score[1, 2] == 2 ||
                score[2, 0] == 2 && score[2, 1] == 2 && score[2, 2] == 2 ||
                score[0, 0] == 2 && score[1, 0] == 2 && score[2, 0] == 2 ||
                score[0, 1] == 2 && score[1, 1] == 2 && score[2, 1] == 2 ||
                score[0, 2] == 2 && score[1, 2] == 2 && score[2, 2] == 2 ||
                score[0, 0] == 2 && score[1, 1] == 2 && score[2, 2] == 2 ||
                score[2, 0] == 2 && score[1, 1] == 2 && score[0, 2] == 2) {
                MessageBox.Show("Blue won!");
                Application.Current.Shutdown();
            }
        }
    }
}
