function verificar() {
    var data = new Date()
    var ano = data.getFullYear()
    var fano = document.getElementById('txtano')
    var res = document.querySelector('div#res')
    if (fano.value.length == 0 || Number(fano.value) > ano) {
        window.alert('[ERRO] Verificar os dados e tente novamente!')
    } else {
        var fsex = document.getElementsByName('radsex')
        var idade = ano - Number(fano.value)
        var genero = ''
        var img = document.createElement('img')
        img.setAttribute('id', 'foto')
        if (fsex[0].checked) {
            genero = 'Homem'
            if (idade >=0 && idade < 10) {
                //CRIANÇA
                img.setAttribute('src', 'homemcrianca.png')
            } else if (idade < 21) {
                //JOVEM
                img.setAttribute('src', 'homemadolescente.png')
            } else if (idade < 50) {
                //IDOSO
                img.setAttribute('src', 'homem.png')
            } else {
                //IDOSO
                img.setAttribute('src', 'homemidoso.png')
            }
        } else if (fsex[1].checked) {
            genero = 'Mulher'
            if (idade >=0 && idade < 10) {
                //CRIANÇA
                img.setAttribute('src', 'mulhercrianca.png')
            } else if (idade < 21) {
                //JOVEM
                img.setAttribute('src', 'mulheradolescente.png')
            } else if (idade < 50) {
                //IDOSO
                img.setAttribute('src', 'mulher.png')
            } else {
                //IDOSO
                img.setAttribute('src', 'mulheridosa.png')
            }
        }
        res.innerHTML = `Detectamos: ${genero} com ${idade} anos`
        res.appendChild(img)
    }
}