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

namespace Minesweeper
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        int[,] board;
        int openedBlocks;
        int width;
        int height;
        int mines;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void startBtn_Click(object sender, RoutedEventArgs e)
        {
            gridContainer.Children.Clear();

            openedBlocks = 0;

            try
            {
                width = int.Parse(inputWidth.Text);
                height = int.Parse(inputHeight.Text);
                mines = int.Parse(inputMines.Text);
            }

            catch
            {
                MessageBox.Show("Invalid input. Width, Height and Mines must be integers");
                return;
            }

            if (mines > height*width)
            {
                MessageBox.Show("Too many mines");
                return;
            }

            init_board(width, height, mines);

            border.Width = width * 25;
            border.Height = height * 25;

            gridContainer.Columns = width;
            gridContainer.Rows = height;
            for (int i = 0; i < gridContainer.Columns * gridContainer.Rows; i++)
            {
                Rectangle block = new Rectangle();
                block.Fill = new SolidColorBrush(Colors.Black);
                block.Margin = new Thickness(0.5);
                block.Cursor = Cursors.Hand;
                block.MouseLeftButtonDown += block_click;
                gridContainer.Children.Add(block);
            }
            gridContainer.IsEnabled = true;
        }

        void block_click(object sender, RoutedEventArgs e)
        {
            var clickedBlock = (sender as Rectangle);

            int rows = gridContainer.Rows;
            int columns = gridContainer.Columns;

            int index = gridContainer.Children.IndexOf(clickedBlock);

            int column = index % columns;
            int row = index / columns;

            string imageUrl = "pack://application:,,,/Images/" + board[row,column].ToString() + ".png";

            clickedBlock.Fill = new ImageBrush
            {
                ImageSource = new BitmapImage(new Uri(imageUrl))
            };
            clickedBlock.IsEnabled = false;

            openedBlocks++;

            if (board[row,column] == 9)
            {
                //MessageBox.Show("You lost");
                //gridContainer.IsEnabled = false;
            }

            else if (openedBlocks >= height*width - mines)
            {
                //MessageBox.Show("You won!");
                //gridContainer.IsEnabled = false;
            }
        }

        void init_board(int columns, int rows, int mines)
        {
            board = new int[rows, columns];
            int minesPlaced = 0;

            Random rnd = new Random();

            while (minesPlaced < mines)
            {
                int x = rnd.Next(columns);
                int y = rnd.Next(rows);

                if (board[y,x] != 9)
                {
                    board[y,x] = 9;
                    updateAdjacentBlocks(x,y);
                    minesPlaced++;
                }
            }
        }

        void updateAdjacentBlocks(int x, int y)
        {
            int xLow = x - 1;
            int xHigh = x + 1;
            int yLow = y - 1;
            int yHigh = y + 1;

            if (xLow < 0)
            {
                xLow = 0;
            }
            if (xHigh >= board.GetLength(1))
            {
                xHigh = board.GetLength(1) - 1;
            }
            if (yLow < 0)
            {
                yLow = 0;
            }
            if (yHigh >= board.GetLength(0))
            {
                yHigh = board.GetLength(0) - 1;
            }

            for (int i = xLow; i <= xHigh; i++)
            {
                for (int j = yLow; j <= yHigh; j++)
                {
                    if(board[j,i] != 9)
                    {
                        board[j,i]++;
                    }
                }
            }
        }
    }
}
