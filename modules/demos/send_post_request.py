import requests
from random import randint

print(requests.post(url="https://flask-scoreboard.herokuapp.com/scoreboard_post",
            json={
                "gameid" : randint(1,10),
                "playerX" : {
                    "score" : randint(1,10)
                },
                "playerY" : {
                    "score" : randint(1,10)
                },
                "stats" : {
                    "some interesting stats" : "stats"
                }
            }).text)

