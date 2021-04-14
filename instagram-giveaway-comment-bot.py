# Creates an instagram comment bot for posting comments on giveaways.
# Feel free to modify this script to fit your specific needs.

tags_filepath="Add tags filepath here"
follower_list_filepath="Add follower list filepath here"
instagram_username="Add your instagram username here"
instagram_password="Add your instagram password here"
username_xpath="Add XPATH for username field here"
password_xpath="Add XPATH for password field here"
comment_box_xpath="Add comment box XPATH for post here"
post_url="Add post URL here"

# modify this value so that instagram does not soft ban you for commenting 
# too frequently. current value is 15 minutes per comment
comment_sleep_time=900

# open tags and follower list files
# feel free to modify the script to include one or both of these according to
# your needs
with open(follower_list_filepath) as f:
    followers = [line.rstrip() for line in f]
with open(tags_filepath) as f:
    randtags = [line.rstrip() for line in f]
        
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import random
class InstagramBot():
  def __init__(self, email, password):
      self.browser = webdriver.Chrome()
      self.email = email
      self.password = password

  def signIn(self):
      self.browser.get('https://www.instagram.com/accounts/login/')

      #wait for fields to be clickable
      emailInput = WebDriverWait(self.browser,20).until(EC.element_to_be_clickable((By.XPATH, username_xpath)))
      passwordInput = WebDriverWait(self.browser,20).until(EC.element_to_be_clickable((By.XPATH, password_xpath))) 

      #enter data in fields and login
      emailInput.send_keys(self.email)
      passwordInput.send_keys(self.password)
      passwordInput.send_keys(Keys.ENTER)
      time.sleep(120)

  #if you need to add tags, use this overload
  def comment(self, follower1, follower2, tag):
      self.browser.get(post_url)
      time.sleep(3)

      comment_box = lambda: WebDriverWait(self.browser, 20).until(EC.element_to_be_clickable((By.XPATH, comment_box_xpath)))

      comment_box().click()

      comment = "@" + follower1 + " @" + follower2+ " " + tag;
      for i in comment:
          comment_box().send_keys(i)
          time.sleep(random.randint(1,7)/30)
      comment_box().send_keys(Keys.SPACE)
      comment_box().send_keys(Keys.ENTER)

  #if you only need to comment users, use this overload
  #modify the number of followers according to your needs
  def comment(self, follower1, follower2, follower3):
      self.browser.get()
      time.sleep(3)

      comment_box = lambda: WebDriverWait(self.browser, 20).until(EC.element_to_be_clickable((By.XPATH, comment_box_xpath)))

      comment_box().click()

      comment1 = "@" + follower1 
      comment2 = " @" + follower2
      comment3 = " @" + follower3

      #emulate typing
      for i in comment1:
          comment_box().send_keys(i)
          time.sleep(random.randint(1,20)/30)

      for i in comment2:
          comment_box().send_keys(i)
          time.sleep(random.randint(1,20)/30)
      for i in comment3:
          comment_box().send_keys(i)
          time.sleep(random.randint(1,20)/30)

      time.sleep(3)

      #post comment
      comment_box().send_keys(Keys.SPACE)
      comment_box().send_keys(Keys.ENTER)

bot = InstagramBot(instagram_username, instagram_password);
bot.signIn();

length = len(followers);

# iterates over the list of followers and picks three at a time
for i in range(0,length-1,3):
    #bot.comment(followers[i],followers[i+1],randtags[i])
    bot.comment(followers[i],followers[i+1], followers[i+2])
    time.sleep(comment_sleep_time) 
