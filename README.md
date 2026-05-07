# AloneZPackZB - Fix Bot Invisivel

## Problema

O bot do AI_Bandits spawna mas fica **invisivel** (so aparece o nome "ALONEZ BOT").

### Causa raiz (encontrada no RPT)

O PBO original do `@AIBandits` define as classes de cabeca assim:

```
class BanditHead_Base : Inventory_Base   // <-- ERRADO!
```

O DayZ exige que classes de cabeca herdem de `Head_Default` (que tem `entityType = HeadType`).

**Erros no RPT:**
```
ENTITY (E): Type 'Inventory_BaseType' must be inherited from class 'HeadType'
ENTITY (E): Type 'BanditHead_Keiko' must be inherited from class 'Head'
```

Sem cabeca valida, o personagem inteiro nao renderiza = **bot invisivel**.

### Outros erros (menores)

| Erro | Causa | Impacto |
|------|-------|---------|
| `Cannot open object simplesurvivors\bandits\proxies\cube_g.p3d` | Proxy model faltando no PBO original | Cosmetic |
| `Shape BanditBody_Base does not have defined min&max for loot's BBox` | BBox nao definido nos modelos originais | Cosmetic |
| `Cannot create non-ai vehicle BanditAI_Mirek` | Classe BanditAI_Mirek faltando ou incompleta | Bot Mirek nao spawna |

---

## Solucao: AloneZPackZB_HeadFix

O arquivo `AloneZPackZB_HeadFix/config.cpp` **sobrescreve** as classes de cabeca do AI_Bandits original, corrigindo a heranca:

```
class BanditHead_Base : Head_Default     // <-- CORRETO!
```

E adiciona as propriedades obrigatorias que faltavam:
- `wounds`
- `selectionHeadWound`
- `selectionPersonality`
- `hiddenSelections/Textures/Materials`

### Como usar

#### Opcao A: PBO separado (recomendado)

1. Empacote a pasta `AloneZPackZB_HeadFix/` como `AloneZPackZB_HeadFix.pbo` usando PBO Manager
2. Coloque o PBO em `@Teste/Addons/` (ao lado do `AloneZPackZB.pbo`)
3. A ordem dos mods pode ficar como esta:
   ```
   -mod=@CF;@MZKOTH;@VPPAdminTools;@Teste;...;@AIBandits
   ```
4. O `requiredAddons[] = {"DZ_Characters_Heads", "AI_Bandits"};` garante que o config do AI_Bandits e processado PRIMEIRO, e depois o nosso override aplica

#### Opcao B: Integrar no AloneZPackZB existente

1. Abra o `config.cpp` do AloneZPackZB
2. Adicione `"AI_Bandits"` no array `requiredAddons[]`:
   ```cpp
   requiredAddons[] = {"DZ_Characters_Heads", "AI_Bandits"};
   ```
3. Copie todo o bloco `class CfgVehicles` do `AloneZPackZB_HeadFix/config.cpp` para dentro do `CfgVehicles` existente
4. Reempacote como `AloneZPackZB.pbo`

### Verificacao no RPT

Apos aplicar o fix, o RPT deve mostrar:

**Sucesso** (linha nova):
```
Updating base class Inventory_Base->Head_Default, by AloneZPackZB_HeadFix\config.bin/CfgVehicles/BanditHead_Base/
```

**Os erros abaixo devem DESAPARECER:**
```
ENTITY (E): Type 'Inventory_BaseType' must be inherited from class 'HeadType'
ENTITY (E): Type 'BanditHead_Keiko' must be inherited from class 'Head'
Warning Message: No entry 'bin\config.bin/CfgVehicles/BanditHead_Keiko.wounds'
Warning Message: No entry 'bin\config.bin/CfgVehicles/BanditHead_Keiko.selectionHeadWound'
Warning Message: No entry 'bin\config.bin/CfgVehicles/BanditHead_Keiko.selectionPersonality'
```

---

## Resumo do RPT Analisado

### Funcionando OK
- AloneZPackZB.pbo carrega
- AI_Bandits.pbo carrega
- Skeleton carrega: `AI_Bandits/anims/bandit_skeleton.anim.xml`
- Scripts AloneZPackZB inicializam (config folder, JSON configs, SpawnManager)
- AnimGraph carrega: `AI_Bandits/anims/animgraph/bandits.agr`
- Bot spawna: `BanditAI_Keiko`
- Bot atira: `Bullet_762x39`

### Precisa Fix
- Cabecas com heranca errada (este fix resolve)
- `BanditAI_Mirek` nao cria (verificar se classe existe no config original)
