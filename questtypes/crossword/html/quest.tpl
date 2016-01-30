<form method="post" class="crossword">
    <table id="matrix">
        <tbody>
            <?php foreach(range(0, $maxY) as $y) : ?>
            <tr>
                <?php foreach(range(0, $maxX) as $x) : ?>
                <td>
                    <?php if(array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) : ?>
                    <?php if(count($matrix[$x][$y]['indices']) > 0) : ?><span class="index"><?=implode('/',array_map(function($e) { return $e+1; }, $matrix[$x][$y]['indices']))?></span><?php endif ?>
                    <input type="text" name="answers[<?=$x?>][<?=$y?>]" maxlength="1" size="1" value="<?=(!is_null($matrix[$x][$y]['answer'])) ? $matrix[$x][$y]['answer'] : ''?>" />
                    <?php endif ?>
                </td>
                <?php endforeach ?>
            </tr>
            <?php endforeach ?>
        </tbody>
    </table>
    <ol>
        <?php foreach($words as &$word) : ?>
        <li>
            <?php if($word['vertical']) : ?>
            <?=_('vertical')?>:
            <?php else : ?>
            <?=_('horizontal')?>:
            <?php endif ?>
            <?=\hhu\z\Utils::t($word['question'])?>
        </li>
        <?php endforeach ?>
    </ol>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
<script type="text/javascript">
// Last position
var posX = 0;
var posX = 0;

// Handle key input
$('input:text').keyup(function(event) {
    // Determine current position
    var row = $(this).closest('tr');
    var y = $('#matrix tr').index(row);
    var col = $(this).closest('td');
    var x = row.children().index(col);

    // Determine current direction
    var horizontal = (x != posX);

    // Set current position
    posX = x;
    posY = y;

    // Next input field
    var nextInput = null;

    // Hanlde keys
    switch(event.keyCode)
    {
        case 37: // Left
            nextInput = getColumnInput(row, x-1);
        break;
        case 38: // Up
            nextInput = getRowInput(x, y-1);
        break;
        case 39: // Right
            nextInput = getColumnInput(row, x+1);
        break;
        case 40: // Down
            nextInput = getRowInput(x, y+1);
        break;
        default:
            // Only handy character input
            if(event.key.length != 1) {
                break;
            }

            // Set new character
            $(this).val(event.key);

            // Go to next input field
            if(horizontal) {
                nextInput = getColumnInput(row, x+1);
            }
            else {
                nextInput = getRowInput(x, y+1);
            }

            event.preventDefault();
        break;
    }

    // Select input field
    if(nextInput != null) {
        nextInput.focus();
    }
});


/**
 * Get the input field of the column x of the given row.
 */
function getColumnInput(row, x)
{
    nextCol = $('td', row)[x];
    if(nextCol != null) {
        return $('input:text', nextCol)[0];
    }
    else {
        // TODO get next number
    }


    return null;
}


/**
 * Get the input field of the column y of row x.
 */
function getRowInput(x, y)
{
    nextRow = $('#matrix tr')[y];
    if(nextRow != null)
    {
        nextCol = $('td', nextRow)[x];
        if(nextCol != null) {
            return $('input:text', nextCol)[0];
        }
    }
    else {
        // TODO get nextnumber
    }


    return null;
}
</script>
