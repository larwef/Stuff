/* This is not an implementation fir for use. It uses huge amounts of resources.
It uses lots of RAM and will probably tank you network. To adress the RAM issue,
i guess you would have to fix the write to file part, an do a more traditional 
open file, write, then close file. And limit the amount of threads running at a
given time. */
package main
 
import (
    "fmt"
    "net/http"
    "io/ioutil"
    "syscall"
    "strings"
    "bufio"
    "os"
    )
 
type Item struct{
	title 	string
	url 	string
	folder	string
};

var finished_chan = make(chan int);

func main() {

	reader := bufio.NewReader(os.Stdin);
	fmt.Print("Enter URL: ");
	input, _ := reader.ReadString('\n');
	url := strings.TrimSuffix(input, "\n");

	items := parse_rss_file(url);

	fmt.Printf("%d items found\n",len(items));

	for i := 0; i < len(items); i++ {
		go download_item(items[i]);
	}

	total := 0;
	success := 0;
	failed := 0;

	for total < len(items){
		val := <-finished_chan;
		total++;
		if val == 1 {
			success++;
		} else {
			failed++;
		}
		fmt.Printf("%d/%d\n", total, len(items));
	}

	fmt.Printf("\n%d successful\n", success);
	fmt.Printf("%d unsuccessful\n", failed);
	fmt.Println("Finished!");
}

func parse_rss_file(rss_url string) []*Item{
	resp, err := http.Get(rss_url);
	if err != nil {
		fmt.Println("Error, couldnt open URL");
		syscall.Exit(1);
	}
	// Defer puts the function call on a list, nd gets called when the sourounding function terminates (either finish or panic)
	defer resp.Body.Close();
	body, err := ioutil.ReadAll(resp.Body);

	items := []*Item{};

	split_str := strings.Split(string(body), "<item>");

	folder_name := "Unknown";

	for i, char := range(split_str) {
		title_start := strings.Index(char, "<title>")+7;
		title_end := strings.Index(char, "</title");
		// char(0) is everything above the first item
		if i > 0 {
			temp := new(Item);

			url_start := strings.Index(strings.ToLower(char), "enclosure url") + 15;
			url_end := strings.Index(strings.ToLower(char), ".mp3") + 4;

			temp.title = char[title_start:title_end];
			temp.url = char[url_start:url_end];
			temp.folder = folder_name;
			items = append(items, temp);
		} else {
			folder_name = char[title_start:title_end];
			err = os.Mkdir(folder_name, 0644);
			if err != nil {
				fmt.Println("Could not create folder, it might exist. In that case the downloads will continue as normal.");
			}
		}
	}

	return items;
}

func download_item(item *Item){
	resp, err := http.Get(item.url);
	if err != nil {
		fmt.Println("Error");
		syscall.Exit(1);
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body);

	err = ioutil.WriteFile(item.folder + "/" + item.title + ".mp3", body, 0644);
	if err != nil {
		fmt.Printf("Trouble downloading %s\n", item.title);
		finished_chan<-0;
		return;
    }
    finished_chan<-1;
}