local webhook = ""
function hook(varlist)
    if varlist[1]:find("The Power of Love") then
log("test")
name = string.match(varlist[1], "Love!(.*)found")
name = name:gsub("`9","")
name = name:gsub("`","")
name = name:gsub("`````5","")
name = name:gsub("`w","")
name = name:gsub("`2","")
name = name:gsub("`4","")
name = name:gsub("`^","")
world = "GHC"
world = world:gsub("`4", "")
world = world:gsub("%$", "")
world = world:gsub("`5","")
world = world:gsub("```$`4" , "")
world = world:gsub("`","")
sb = varlist[1]
sb = sb:gsub("%`.", "")

local payload = [[{
    "content": "",
    "embeds": [{
        "title": "lucky dog: ```]] .. name .. [[```",
        "description": "(script by<@1009032206615846952>)  ```]] .. sb .. [[```",
        "url": "https://avatarfiles.alphacoders.com/334/334449.png",
        "color": 69,
        "fields": [{
            "name": "",
            "value": ""
        }],
        "author": {
            "name": "",
            "url": "https://avatarfiles.alphacoders.com/334/334449.png",
            "icon_url": "https://avatarfiles.alphacoders.com/334/334449.png"
        },
        "footer": {
            "text": "item: ]] .. world .. [[ ",
            "icon_url": ""
        },
        "timestamp": ""
    }]
}]]
SendWebhook(webhook, payload)
end
end
AddCallback("hook","OnVarlist", hook)