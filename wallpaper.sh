#fetch json format of bing daily wallpaper, parse it using jq and add it to the bing url to get the photo, then save it in .desktop.jpg
curl -s http://bing.com$(curl -s http://www.bing.com/HPImageArchive.aspx\?format\=js\&idx\=0\&n\=1 | jq -r '.images[0].url') > ~/.desktop.jpg

#set wallpaper and generate colorscheme based on it. remove photo afterwards
feh --bg-fill ~/.desktop.jpg
rm ~/.desktop.jpg
