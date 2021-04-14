#Instagram Like and Comment Bot

#Uses most popular hashtags to comment and like photos
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import re
import time
from bs4 import BeautifulSoup as bs
from urllib.request import urlopen



tags = (
'happy','cute','tbt','like4like','followme',
'photooftheday','fashion','beautiful',
'picoftheday','follow','selfie','summer',
'art','instadaily','friends','repost','nature',
'fun','style','smile','food','cats','dogs','gym'
)

class LikeBot:
    def __init__(self):
        self.bot = webdriver.Firefox()

    def like_photo(self,tag,comment):
        bot = self.bot
        bot.get(f"https://www.instagram.com/explore/tags/{tag}/")
        while True:
            for i in range(4):
                bot.execute_script("window.scrollTo(0,document.body.scrollHeight)")
                time.sleep(3)
            #get photo url
            #posts = bot.find_elements_by_class_name("v1Nh3")
            links =[]
            source = bot.page_source
            data=bs(source, 'html.parser')
            body = data.find('body')
            script = body.find('span')
            for link in script.findAll('a'):
                if re.match("/p", link.get('href')):
                    links.append('https://www.instagram.com'+link.get('href'))

            time.sleep(10)

            for page in links:
                bot.get(page)
                try:
                    div = bot.find_element_by_class_name("Ypffh")
                    div.click()
                    div = bot.find_element_by_class_name("Ypffh")
                    div.clear()
                    div = bot.find_element_by_class_name("Ypffh")
                    div.send_keys(comment)
                    div = bot.find_element_by_class_name("Ypffh")
                    div.send_keys(Keys.RETURN)
                    time.sleep(70)

                    div = bot.find_elements_by_class_name("dCJp8")
                    for elem in div :
                        like = elem.find_element_by_class_name("glyphsSpriteHeart__outline__24__grey_9")   
                        like.click()
                        break
                    time.sleep(70)
                    
                except Exception as ex:
                    time.sleep(60)
                

liker = LikeBot()
time.sleep(30)
for tag in tags:
    liker.like_photo(tag,"Awesome post, keep it up!")