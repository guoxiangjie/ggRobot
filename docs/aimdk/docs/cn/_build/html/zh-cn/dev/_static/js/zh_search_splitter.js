var splitQuery = (query) => {
  const CJK_RANGE = /[\u4e00-\u9fff\u3400-\u4dbf\uf900-\ufaff]/;
  const NON_WORD = /[^\p{Letter}\p{Number}_\p{Emoji_Presentation}]+/gu;

  const parts = query.split(NON_WORD).filter(term => term);
  const result = [];

  for (const part of parts) {
    if (CJK_RANGE.test(part)) {
      const cjkChars = [];
      const latinBuf = [];
      for (const ch of part) {
        if (CJK_RANGE.test(ch)) {
          if (latinBuf.length) {
            result.push(latinBuf.join(''));
            latinBuf.length = 0;
          }
          cjkChars.push(ch);
        } else {
          if (cjkChars.length) {
            _pushCjkTerms(result, cjkChars);
            cjkChars.length = 0;
          }
          latinBuf.push(ch);
        }
      }
      if (cjkChars.length) {
        _pushCjkTerms(result, cjkChars);
      }
      if (latinBuf.length) {
        result.push(latinBuf.join(''));
      }
    } else {
      result.push(part);
    }
  }
  return result;
};

function _inIndex(word) {
  if (typeof Search !== "undefined" && Search._index) {
    var terms = Search._index.terms;
    var titleTerms = Search._index.titleterms;
    return (terms && word in terms) || (titleTerms && word in titleTerms);
  }
  return false;
}

function _pushCjkTerms(result, cjkChars) {
  const full = cjkChars.join('');
  if (_inIndex(full)) result.push(full);
  var found = [];
  for (let len = Math.min(cjkChars.length - 1, 4); len >= 2; len--) {
    for (let i = 0; i <= cjkChars.length - len; i++) {
      const sub = cjkChars.slice(i, i + len).join('');
      if (_inIndex(sub)) found.push(sub);
    }
  }
  if (found.length > 0) {
    for (const w of found) result.push(w);
  } else if (!_inIndex(full)) {
    for (let i = 0; i < cjkChars.length - 1; i++) {
      result.push(cjkChars[i] + cjkChars[i + 1]);
    }
  }
}

var Scorer = {
  objNameMatch: 11,
  objPartialMatch: 6,
  objPrio: { 0: 15, 1: 5, 2: -5 },
  objPrioDefault: 0,
  title: 15,
  partialTitle: 7,
  term: 5,
  partialTerm: 2
};

document.addEventListener("DOMContentLoaded", function () {
  if (typeof Search === "undefined") return;

  Search.performTermsSearch = function (searchTerms, excludedTerms) {
    var terms = Search._index.terms;
    var titleTerms = Search._index.titleterms;
    var filenames = Search._index.filenames;
    var docNames = Search._index.docnames;
    var titles = Search._index.titles;

    var scoreMap = new Map();
    var fileMap = new Map();

    searchTerms.forEach(function (word) {
      var arr = [
        { files: terms[word], score: Scorer.term },
        { files: titleTerms[word], score: Scorer.title }
      ];
      if (word.length > 2) {
        var escaped = word.replace(/[.*+\-?^${}()|[\]\\]/g, "\\$&");
        if (!terms.hasOwnProperty(word)) {
          Object.keys(terms).forEach(function (term) {
            if (term.match(escaped))
              arr.push({ files: terms[term], score: Scorer.partialTerm });
          });
        }
        if (!titleTerms.hasOwnProperty(word)) {
          Object.keys(titleTerms).forEach(function (term) {
            if (term.match(escaped))
              arr.push({ files: titleTerms[term], score: Scorer.partialTitle });
          });
        }
      } else {
        var re = new RegExp("^" + word.replace(/[.*+\-?^${}()|[\]\\]/g, "\\$&"));
        Object.keys(terms).forEach(function (term) {
          if (term !== word && re.test(term))
            arr.push({ files: terms[term], score: Scorer.partialTerm });
        });
        Object.keys(titleTerms).forEach(function (term) {
          if (term !== word && re.test(term))
            arr.push({ files: titleTerms[term], score: Scorer.partialTitle });
        });
      }

      if (arr.every(function (r) { return r.files === undefined; })) return;

      arr.forEach(function (record) {
        if (record.files === undefined) return;
        var recordFiles = Array.isArray(record.files) ? record.files : [record.files];
        recordFiles.forEach(function (file) {
          if (!scoreMap.has(file)) scoreMap.set(file, {});
          var cur = scoreMap.get(file)[word] || 0;
          if (record.score > cur) scoreMap.get(file)[word] = record.score;
          if (!fileMap.has(file)) fileMap.set(file, [word]);
          else if (fileMap.get(file).indexOf(word) === -1) fileMap.get(file).push(word);
        });
      });
    });

    var results = [];
    var excludeSet = new Set();
    excludedTerms.forEach(function (term) {
      var f = terms[term];
      if (f !== undefined) {
        (Array.isArray(f) ? f : [f]).forEach(function (x) { excludeSet.add(x); });
      }
      f = titleTerms[term];
      if (f !== undefined) {
        (Array.isArray(f) ? f : [f]).forEach(function (x) { excludeSet.add(x); });
      }
    });

    fileMap.forEach(function (wordList, file) {
      if (excludeSet.has(file)) return;
      var totalScore = 0;
      wordList.forEach(function (w) {
        var s = scoreMap.get(file)[w];
        totalScore += s * w.length;
      });
      var ratio = wordList.length / searchTerms.size;
      var score = Math.round(totalScore * ratio * ratio);
      results.push([docNames[file], titles[file], "", null, score, filenames[file], "text"]);
    });

    return results;
  };
});
