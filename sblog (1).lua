local webhook = "LINK"
function hook(varlist)
    if varlist[1]:find("[SB]") then
name = string.match(varlist[1], "%(([^%)]+)%)")
name = name:gsub("`9","")
name = name:gsub("`````5","")
name = name:gsub("`w","")
name = name:gsub("`2","")
name = name:gsub("`4","")
name = name:gsub("`^","")
world = string.match(varlist[1], "in (.-) %*")
world = world:gsub("`4", "")
world = world:gsub("%$", "")
world = world:gsub("`5","")
world = world:gsub("```$`4" , "")
world = world:gsub("`","")
sb = varlist[1]:match("%*%*%s*:%s*(.+)")
sb = sb:gsub("%`.", "")

local payload = [[{
    "content": "",
    "embeds": [{
        "title": "SB by: ```]] .. name .. [[```",
        "description": "(script by<@1009032206615846952>) SB: ```]] .. sb .. [[```",
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
            "text": "In: ]] .. world .. [[ ",
            "icon_url": ""
        },
        "timestamp": ""
    }]
}]]
SendWebhook(webhook, payload)
end
end
AddCallback("hook","OnVarlist", hook)