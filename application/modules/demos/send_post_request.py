import requests
from random import randint

print(requests.post(url="http://127.0.0.1:5000/scoreboard_post",
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

