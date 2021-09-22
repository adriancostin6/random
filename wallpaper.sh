prevwall=$HOME/.config/prev-wallpaper.jpg
wall=$HOME/.config/wallpaper.jpg

feh --bg-fill $prevwall

wget -q -O $wall https://source.unsplash.com/1920x1080/?nature,animals

cp $wall $prevwall

feh --bg-fill $wall
